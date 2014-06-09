
#include "GameScene.h"

#include <random>
#include <algorithm>

#define zBack 0

GameScene::~GameScene() {
    
}

GameScene::GameScene(): Layer() {
    
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

    
    return true;
}
