//
//  GameUI.h
//  urbanaria
//
//  Created by reenboog on 16.06.14.
//
//

#ifndef __urbanaria__GameUI__
#define __urbanaria__GameUI__

#include "cocos2d.h"

USING_NS_CC;

class GameUI: public Layer {
public:
    GameUI();
    virtual ~GameUI();
    
    static GameUI* create();
    bool init();
    
    void setTime(int time);
    void setScore(int score);
    
    void popUp();
    void popOut();
private:
    Label *timeLabel;
    Label *scoreLabel;
};

#endif /* defined(__urbanaria__GameUI__) */
