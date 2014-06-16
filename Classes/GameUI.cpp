//
//  GameUI.cpp
//  urbanaria
//
//  Created by reenboog on 16.06.14.
//
//

#include "GameUI.h"
#include <string>

using namespace std;

#define kScoreFont "gameUIScore.fnt"
#define kTimePassedFont kScoreFont

GameUI::GameUI(): Layer() {
    this->timeLabel = nullptr;
    this->scoreLabel = nullptr;
}

GameUI::~GameUI() {
    
}

GameUI* GameUI::create() {
    GameUI *node = new GameUI();
    if(node && node->init()) {
        node->autorelease();
        return node;
    } else {
        delete node;
        node = nullptr;
        return node;
    }
}

bool GameUI::init() {
    if(!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    timeLabel = Label::createWithBMFont(kTimePassedFont, "00:00");
    timeLabel->setPosition({visibleSize.width * 0.45, visibleSize.height * 0.9});

    this->addChild(timeLabel);

    scoreLabel = Label::createWithBMFont(kScoreFont, "0");
    scoreLabel->setPosition({visibleSize.width * 0.55, visibleSize.height * 0.9});

    this->addChild(scoreLabel);
    
    return true;
}

void GameUI::popUp() {
    
}

void GameUI::popOut() {
    
}

void GameUI::setTime(int time) {
    string timeStr = "";

    int seconds = time;

    int min = seconds / 60;
    int sec = seconds % 60;

    if(min < 10) {
        timeStr += StringUtils::format("0%i:", min);
    } else {
        timeStr += StringUtils::format("%i:", min);
    }

    if(sec < 10) {
        timeStr += StringUtils::format("0%i", sec);
    } else {
        timeStr += StringUtils::format("%i", sec);
    }
    
    timeLabel->setString(timeStr);
}

void GameUI::setScore(int score) {
    scoreLabel->setString(StringUtils::format("%i", score));
}