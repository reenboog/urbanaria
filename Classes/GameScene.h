#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class GameScene: public Layer {
public:
    virtual ~GameScene();

    static Scene* scene();
    virtual bool init();
    
    GameScene();
    
    CREATE_FUNC(GameScene);
    
    // touches
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
    void generateNextCircle();
    void applyValues();
    void onValuesApplied();
    
    void onGameOver();
    
    void update(float dt);
    void onScoreApplied();
    
    bool cacheCurrentValue();
private:
    float timePassed;
    int score;
    
    Label *timeLabel;
    Label *scoreLabel;
    
    Sprite *back;
    
    Sprite *redBig;
    Label *redBigLabel;
    
    Sprite *redSmall;
    Label *redSmallLabel;
    
    Sprite *blueBig;
    Label *blueBigLabel;
    
    Sprite *blueSmall;
    Label *blueSmallLabel;
    
    Sprite *black;
    Label *blackLabel;
    
    Node *nodeBeingDragged;
    
    Point draggedNodePrevPos;
    
    bool dragEnabled;
    
    vector<Sprite*> greenCircles;
};

#endif // __HELLOWORLD_SCENE_H__
