#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "IWatcher.h"

USING_NS_CC;

using namespace std;

class FieldNode;
class NumericTemporaryNode;
class GeneratableNumericNode;
class NumericNode;

class GameScene: public Layer, public IFieldWatcher, IGeneratableNumericWatcher, ITemporaryNumericWatcher {
public:
    virtual ~GameScene();

    static Scene* scene();
    virtual bool init();
    
    GameScene();
    
    CREATE_FUNC(GameScene);
    
    // IFieldWatcher callbacks
    // IGeneratableNumericWatcher callbacks
    void onNodeTransitedIn();
    void onNodeTransitedOut();
    void onValueGenerated();
    
    // ITemporaryNumericWatcher
    void onValueCached();
    
    // touches
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
    void generateNextValue();
    void onValuesApplied(int valueDiff);
    
    void update(float dt);
    void onScoreApplied(int score);
    
    bool cacheCurrentValue();
private:
    void onGameOver();

    void popUp();
    void popOut();
private:
    float timePassed;
    int score;
    
    FieldNode *leftField;
    FieldNode *rightField;
    
    GeneratableNumericNode *generatable;
    
    bool dragEnabled;
    vector<NumericTemporaryNode*> temporaryBoxes;
    
    NumericNode *nodeBeingDragged;
    Point draggedNodePrevPos;
    
    Sprite *back;
};

#endif // __HELLOWORLD_SCENE_H__
