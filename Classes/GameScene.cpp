
#include "GameScene.h"

#include <random>
#include <algorithm>

#define zBack 0
#define zBlack 5
#define kNumberOfGreenCircles 3

#define kMaxValueToMine 16

GameScene::~GameScene() {
    
}

GameScene::GameScene(): Layer() {
    nodeBeingDragged = nullptr;
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
    if (!Layer::init()) {
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
    
    // circles
    {
        // blue
        blueBig = Sprite::create("blueBig.png");
        blueBig->setPosition({visibleSize.width * 0.3, visibleSize.height * 0.5});
        blueBig->setTag(1);
        
        this->addChild(blueBig);
        
        blueBigLabel = Label::createWithBMFont("mainFont.fnt", "1");
        blueBigLabel->setPosition({blueBig->getContentSize().width * 0.5, blueBig->getContentSize().height * 0.5});

        blueBig->addChild(blueBigLabel);
        
        blueSmall = Sprite::create("blueSmall.png");
        blueSmall->setPosition({0, 20});
        blueSmall->setTag(0);

        blueBig->addChild(blueSmall);
        
        blueSmallLabel = Label::createWithBMFont("mainFont.fnt", "0");
        blueSmallLabel->setPosition({blueSmall->getContentSize().width * 0.5, blueSmall->getContentSize().height * 0.5});
        
        blueSmall->addChild(blueSmallLabel);
        
        // red
        
        redBig = Sprite::create("redBig.png");
        redBig->setPosition({visibleSize.width * 0.7, visibleSize.height * 0.5});
        redBig->setTag(1);
        
        this->addChild(redBig);
        
        redBigLabel = Label::createWithBMFont("mainFont.fnt", "1");
        redBigLabel->setPosition({redBig->getContentSize().width * 0.5, redBig->getContentSize().height * 0.5});
        
        redBig->addChild(redBigLabel);
        
        redSmall = Sprite::create("redSmall.png");
        redSmall->setPosition({redBig->getContentSize().width, 20});
        redSmall->setTag(0);
        
        redBig->addChild(redSmall);
        
        redSmallLabel = Label::createWithBMFont("mainFont.fnt", "0");
        redSmallLabel->setPosition({redSmall->getContentSize().width * 0.5, redSmall->getContentSize().height * 0.5});
        
        redSmall->addChild(redSmallLabel);
        
        // black
        black = Sprite::create("black.png");
        black->setPosition({visibleSize.width * 0.5, visibleSize.height * 0.5});
        black->setTag(0);
        
        this->addChild(black, zBlack);
        
        blackLabel = Label::createWithBMFont("mainFont.fnt", "0");
        blackLabel->setPosition({black->getContentSize().width * 0.5, black->getContentSize().height * 0.5});
        
        black->addChild(blackLabel);


        // green circles
        for(int i = 0; i < kNumberOfGreenCircles; ++i) {
            Sprite *green = Sprite::create("green.png");
            
            green->setPosition({visibleSize.width * 0.5 - 0.5 * kNumberOfGreenCircles * green->getContentSize().width +
                                i * green->getContentSize().width + green->getContentSize().width -
                                green->getContentSize().width * 0.5,
                visibleSize.height * 0.15});
            
            greenCircles.push_back(green);
            this->addChild(green);
            
            green->setTag(0);
            
            Label *greenLabel = Label::createWithBMFont("mainFont.fnt", "0");
            greenLabel->setPosition({green->getContentSize().width * 0.5, green->getContentSize().height * 0.5});
            
            green->addChild(greenLabel);
            green->setUserData(greenLabel);
        }
    }

    // set up touches
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->dragEnabled = true;
    
    // generate circles
    this->generateNextCircle();
    
    return true;
}

// touches
bool GameScene::onTouchBegan(Touch* touch, Event  *event) {
    if(!dragEnabled) {
        return false;
    }
    
    Point location = touch->getLocation();

    if(black->getBoundingBox().containsPoint(location)) {
        nodeBeingDragged = black;
        
        draggedNodePrevPos = black->getPosition();
        
        return true;
    }
    
    // check cached values
    for(int i = 0; i < greenCircles.size(); ++i) {
        Node *circle = greenCircles[i];
        if(circle->getBoundingBox().containsPoint(location) && circle->getTag() != 0) {
            nodeBeingDragged = circle;
            draggedNodePrevPos = circle->getPosition();
         
            return true;
        }
    }
    
    return false;
}

void GameScene::onTouchEnded(Touch* touch, Event  *event) {
    if(nodeBeingDragged) {
        if(nodeBeingDragged == black) {
            
            if(blueBig->getBoundingBox().containsPoint(nodeBeingDragged->getPosition())) {
                dragEnabled = false;
                
                blueSmall->setTag(blueSmall->getTag() + nodeBeingDragged->getTag());
                
                applyValues();
            } else if(redBig->getBoundingBox().containsPoint(nodeBeingDragged->getPosition())) {
                dragEnabled = false;
                
                redSmall->setTag(redSmall->getTag() + nodeBeingDragged->getTag());
                
                applyValues();
            } else if(black->getScale() < 1.0){
                if(this->cacheCurrentValue()) {
                    this->generateNextCircle();
                }
            }
            
            
        } else {
            if(blueBig->getBoundingBox().containsPoint(nodeBeingDragged->getPosition())) {
                dragEnabled = false;
                
                blueSmall->setTag(blueSmall->getTag() + nodeBeingDragged->getTag());
                
                nodeBeingDragged->setTag(0);
                nodeBeingDragged->setScale(1.0);
                Label *circleLabel = static_cast<Label*>(nodeBeingDragged->getUserData());
                circleLabel->setString(StringUtils::format("%i", nodeBeingDragged->getTag()));
                
                applyValues();
            } else if(redBig->getBoundingBox().containsPoint(nodeBeingDragged->getPosition())) {
                dragEnabled = false;
                
                redSmall->setTag(redSmall->getTag() + nodeBeingDragged->getTag());
                
                nodeBeingDragged->setTag(0);
                nodeBeingDragged->setScale(1.0);
                Label *circleLabel = static_cast<Label*>(nodeBeingDragged->getUserData());
                circleLabel->setString(StringUtils::format("%i", nodeBeingDragged->getTag()));
                
                applyValues();
            }
        }
        
        nodeBeingDragged->setPosition(draggedNodePrevPos);
    }
    
    black->setScale(1.0);
    black->setOpacity(255);
    
    nodeBeingDragged = nullptr;
}

void GameScene::onTouchMoved(Touch* touch, Event  *event) {
    Point location = touch->getLocation();
    
    if(nodeBeingDragged) {
        if(nodeBeingDragged == black) {
            // check intersection with green circles
            black->setScale(1.0);
            black->setOpacity(255);
            
            for(int i = 0; i < greenCircles.size(); ++i) {
                Sprite *circle = greenCircles[i];

                if(black->getBoundingBox().intersectsRect(circle->getBoundingBox())) {
                    black->setScale(0.6);
                    black->setOpacity(160);
                    break;
                }
            }
        }
        
        nodeBeingDragged->setPosition(location);
    }
}

void GameScene::onTouchCancelled(Touch* touch, Event  *event) {
    if(nodeBeingDragged) {
        if(nodeBeingDragged == black) {
            black->setPosition(draggedNodePrevPos);
        }
    }
    
    nodeBeingDragged = nullptr;

    black->setScale(1.0);
    black->setOpacity(255);
}

// logic

void GameScene::applyValues() {
    blueSmallLabel->setString(StringUtils::format("%i", blueSmall->getTag()));
    redSmallLabel->setString(StringUtils::format("%i", redSmall->getTag()));
    
    this->runAction(Sequence::create(DelayTime::create(1.0),
                                     CallFunc::create([this]() {
                                        this->onValuesApplied();
                                     }),
                                     NULL));
}

void GameScene::onValuesApplied() {
    if(blueBig->getTag() == blueSmall->getTag()) {
        blueBig->setTag(blueBig->getTag() + 1);
        blueSmall->setTag(0);
    } else if(blueBig->getTag() < blueSmall->getTag()) {
        blueBig->setTag(blueBig->getTag() - (blueSmall->getTag() - blueBig->getTag()));
        blueSmall->setTag(0);
    }
    
    if(redBig->getTag() == redSmall->getTag()) {
        redBig->setTag(redBig->getTag() + 1);
        redSmall->setTag(0);
    } else if(redBig->getTag() < redSmall->getTag()) {
        redBig->setTag(redBig->getTag() - (redSmall->getTag() - redBig->getTag()));
        redSmall->setTag(0);
    }
    
    blueBigLabel->setString(StringUtils::format("%i", blueBig->getTag()));
    blueSmallLabel->setString(StringUtils::format("%i", blueSmall->getTag()));
    
    redBigLabel->setString(StringUtils::format("%i", redBig->getTag()));
    redSmallLabel->setString(StringUtils::format("%i", redSmall->getTag()));
    
    if(blueBig->getTag() == redBig->getTag() && blueBig->getTag() == kMaxValueToMine) {
        this->onGameOver();
    } else {
        this->dragEnabled = true;
        this->generateNextCircle();
    }
}

bool GameScene::cacheCurrentValue() {
    for(int i = 0; i < greenCircles.size(); ++i) {
        Sprite *circle = greenCircles[i];
        
        if(circle->getTag() == 0) {
            circle->setTag(black->getTag());
            circle->setScale(1.1);
            
            Label *circleLabel = static_cast<Label*>(circle->getUserData());
            circleLabel->setString(StringUtils::format("%i", circle->getTag()));
            
            return true;
        }
    }
    
    return false;
}

void GameScene::generateNextCircle() {
    int maxValue = blueBig->getTag() > redBig->getTag() ? blueBig->getTag() : redBig->getTag();

    int value = std::max(1, rand() % maxValue);
    
    black->setTag(value);
    
    blackLabel->setString(StringUtils::format("%i", static_cast<int>(black->getTag())));
}

void GameScene::onGameOver() {
    
}