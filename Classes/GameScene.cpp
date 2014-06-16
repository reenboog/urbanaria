
#include "GameScene.h"

#include "GeneratableNumericNode.h"
#include "NumericTemporaryNode.h"
#include "FieldNode.h"
#include "GameUI.h"

#include <random>
#include <algorithm>

#define zBack 0
#define zField 2
#define zTmpBox 3
#define zGeneratable 5
#define zUI 10
#define kNumberOfTemporaryBoxes 3

GameScene::~GameScene() {
    
}

GameScene::GameScene(): Layer() {
    nodeBeingDragged = nullptr;
    
    this->leftField = nullptr;
    this->rightField = nullptr;
    
    this->generatable = nullptr;
    
    this->ui = nullptr;
    
    this->dragEnabled = false;
}

Scene* GameScene::scene() {
    random_device rd;
    srand(rd());
    
    auto scene = Scene::create();
    auto layer = GameScene::create();

    scene->addChild(layer);

    return scene;
}

bool GameScene::init() {
    if(!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // back
    {
        back = Sprite::create("back.png");
        back->setPosition({visibleSize.width / 2.0, visibleSize.height / 2.0});
        
        Size backSize = back->getContentSize();
        
        float backScale = 0.0;
        
        if(backSize.width < visibleSize.width) {
            backScale = visibleSize.width / backSize.width;
        }
        
        if(backScale < visibleSize.height / backSize.height) {
            backScale = visibleSize.height / backSize.height;
        }
        
        back->setScale(backScale);
        
        this->addChild(back, zBack);
    }
    
    {
        // time and score labels
        timePassed = 0.0;
        score = 0;
    }
    
    {
        // fields
        leftField = FieldNode::create(FieldNode::FieldType::FT_Left);
        leftField->setPosition({visibleSize.width * 0.25, visibleSize.height * 0.5});
        leftField->setHigher(kFieldMinValue);
        
        leftField->addStateWatcher(this);

        this->addChild(leftField, zField);
       
        rightField = FieldNode::create(FieldNode::FieldType::FT_Right);
        rightField->setPosition({visibleSize.width * 0.75, visibleSize.height * 0.5});
        rightField->setHigher(kFieldMinValue);
        
        rightField->addStateWatcher(this);
       
        this->addChild(rightField, zField);
    }
    
    {
        // a node generating numbers
        generatable = GeneratableNumericNode::create();
        generatable->setPosition({visibleSize.width * 0.5, visibleSize.height * 0.5});
        
        this->addChild(generatable, zGeneratable);
        
        // subscribe for generatable's state
        generatable->addStateWatcher(this);
    }
    
    {
        // temporary boxes
        for(int i = 0; i < kNumberOfTemporaryBoxes; ++i) {
            NumericTemporaryNode *tmpBox = NumericTemporaryNode::create();
            
            tmpBox->setPosition({visibleSize.width * 0.5 - 0.5 * kNumberOfTemporaryBoxes * tmpBox->getContentSize().width +
                                i * tmpBox->getContentSize().width + tmpBox->getContentSize().width - tmpBox->getContentSize().width * 0.5,
                                visibleSize.height * 0.15});
            
            tmpBox->addStateWatcher(this);
            
            temporaryBoxes.push_back(tmpBox);
            this->addChild(tmpBox, zTmpBox);
        }
    }
    
    {
        // game ui
        this->ui = GameUI::create();
        this->addChild(ui, zUI);
    }

    // set up touches
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // generate a number
    // show fields
    this->generateNextValue();
    this->popUp();
    
    this->scheduleUpdate();
    
    return true;
}

// touches
bool GameScene::onTouchBegan(Touch* touch, Event  *event) {
    if(!dragEnabled) {
        return false;
    }
    
    Point location = touch->getLocation();

    if(generatable->getBoundingBox().containsPoint(location)) {
        nodeBeingDragged = generatable;
        
        draggedNodePrevPos = generatable->getPosition();
        
        return true;
    }
    
    // check cached values
    for(int i = 0; i < temporaryBoxes.size(); ++i) {
        NumericTemporaryNode *tmp = temporaryBoxes[i];

        if(tmp->getBoundingBox().containsPoint(location) && tmp->getValue() != 0) {
            nodeBeingDragged = tmp;
            draggedNodePrevPos = tmp->getPosition();
         
            return true;
        }
    }
    
    return false;
}

void GameScene::onTouchEnded(Touch *touch, Event *event) {
    if(nodeBeingDragged) {
        if(nodeBeingDragged == generatable) {
            
            if(leftField->getHigherValue() < kFieldMaxValue && leftField->getBoundingBox().containsPoint(nodeBeingDragged->getPosition())) {
                dragEnabled = false;
                
                int value = nodeBeingDragged->getValue();
                nodeBeingDragged->setValue(0);
                leftField->applyValue(value);
                // apply values
            } else if(rightField->getHigherValue() < kFieldMaxValue && rightField->getBoundingBox().containsPoint(nodeBeingDragged->getPosition())) {
                dragEnabled = false;
                
                int value = nodeBeingDragged->getValue();
                
                nodeBeingDragged->setValue(0);
                rightField->applyValue(value);
                // apply values
            } else {
                for(int i = 0; i < temporaryBoxes.size(); ++i) {
                    NumericTemporaryNode *tmp = temporaryBoxes[i];
                    
                    if(generatable->getBoundingBox().intersectsRect(tmp->getBoundingBox())) {
                        // cache the value
                        this->cacheCurrentValueMayBe();
                        break;
                    }
                }
            }
            
        } else {
            // so, we assume a temporary number is being dragged right now
            if(leftField->getHigherValue() < kFieldMaxValue && leftField->getBoundingBox().containsPoint(nodeBeingDragged->getPosition())) {
                this->dragEnabled = false;
                // apply some effects to a temporary box maybe
                int value = nodeBeingDragged->getValue();
                nodeBeingDragged->setValue(0);

                leftField->applyValue(value);
            } else if(rightField->getHigherValue() < kFieldMaxValue && rightField->getBoundingBox().containsPoint(nodeBeingDragged->getPosition())) {
                this->dragEnabled = false;
                
                int value = nodeBeingDragged->getValue();
                nodeBeingDragged->setValue(0);

                rightField->applyValue(value);
            }
        }
        
        nodeBeingDragged->setPosition(draggedNodePrevPos);
        //nodeBeingDragged->setScale(1.0);
        
        nodeBeingDragged = nullptr;
    }
}

void GameScene::onTouchMoved(Touch* touch, Event  *event) {
    Point location = touch->getLocation();
    
    if(nodeBeingDragged) {
        if(nodeBeingDragged == generatable) {
            for(int i = 0; i < temporaryBoxes.size(); ++i) {
//                NumericTemporaryNode *tmp = temporaryBoxes[i];

//                if(generatable->getBoundingBox().intersectsRect(tmp->getBoundingBox())) {
//                    generatable->setScale(0.6);
//                    generatable->setOpacity(160);
//                    break;
//                }
            }
        }
        
        nodeBeingDragged->setPosition(location);
    }
}

void GameScene::onTouchCancelled(Touch* touch, Event  *event) {
    if(nodeBeingDragged) {
        if(nodeBeingDragged == generatable) {
            generatable->setPosition(draggedNodePrevPos);
        }
        
        //nodeBeingDragged->setScale(1.0);
        nodeBeingDragged = nullptr;
    }
}

// logic

void GameScene::onValuesApplied(int valueDiff) {
    if(valueDiff > 0) {
        this->onScoreApplied(valueDiff);
    }

    if(leftField->getHigherValue() == rightField->getHigherValue() && leftField->getHigherValue() == kFieldMaxValue) {
        this->onGameOver();
    } else {
        this->dragEnabled = true;
        this->generateNextValue();
    }
}

void GameScene::onScoreApplied(int score) {
    this->score += 10 * score;
    
    ui->setScore(this->score);
    
    //scoreLabel->setString(StringUtils::format("%i", this->score));
}

bool GameScene::cacheCurrentValueMayBe() {
    for(int i = 0; i < temporaryBoxes.size(); ++i) {
        NumericNode *tmp = temporaryBoxes[i];
        
        if(tmp->getValue() == 0) {
            this->dragEnabled = false;
            int value = generatable->getValue();
            generatable->setValue(0);
            tmp->setValue(value);
            //tmp->setScale(1.1);
            
            return true;
        }
    }
    
    return false;
}

void GameScene::generateNextValue() {
    int maxValue = leftField->getHigherValue() > rightField->getHigherValue() ? leftField->getHigherValue() : rightField->getHigherValue();
    int value = std::max(kFieldMinValue, rand() % maxValue);
    
    generatable->setValue(value);
}

void GameScene::update(float dt) {
    this->timePassed += dt;

    ui->setTime(this->timePassed);
}

void GameScene::onGameOver() {
    
}

void GameScene::popUp() {
    generatable->popUp();
    ui->popUp();
    // fields: popUp
}

void GameScene::popOut() {
    generatable->popOut();
    ui->popOut();
}

// IFieldWatcher callbacks
// todo

// IGeneratableNumericWatcher callbacks

void GameScene::onNodeTransitedIn() {
    this->dragEnabled = true;
}

void GameScene::onNodeTransitedOut() {
    
}

void GameScene::onValueGenerated() {
    this->dragEnabled = true;
}

void GameScene::onValueCached() {
    //this->dragEnabled = true;
    this->generateNextValue();
}