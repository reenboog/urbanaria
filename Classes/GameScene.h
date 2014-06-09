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
private:
    Sprite *back;
};

#endif // __HELLOWORLD_SCENE_H__
