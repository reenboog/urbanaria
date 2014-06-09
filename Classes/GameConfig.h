//
//  GameConfig.h
//  solveMe
//
//  Created by Alex Gievsky on 11.11.13.
//
//

#ifndef __solveMe__GameConfig__
#define __solveMe__GameConfig__

#include "cocos2d.h"

USING_NS_CC;

#define kAppVersion         1

class GameConfig {
private:
    GameConfig();
    void setDesignLayoutSize(const Size &size);
    void setVisibleOrigin(const Point &point);
public:
    ~GameConfig();
    
    void load();
    void save();
    
    Size getDesignLayoutSize();
    Point getVisibleOrigin();
    
    bool areRemoteNotificationsEnabled();
    void setRemoteNotificationsEnabled(bool enabled);
    
    bool isAppAlreadyRated();
    void setAppRated(bool rated);
    
    bool wasRateBadgeAlreadyShown();
    void setRateBadgeAlreadyShown(bool shown);
    
    void setMusicVolume(float volume);
    float getMusicVolume();
    
    void setCurrentLanguageType(int type);
    int getCurrentLanguageType();
    
    void setSoundVolume(float volume);
    float getSoundVolume();

    void loadFilePaths();
    
    static GameConfig* sharedInstance();
    static void purge();
private:
    static GameConfig *__sharedInstance;
    
    Point visibleOrigin;
    Size designLayoutSize;
    
    bool rateBadgeWasAlreadyShown;
    bool remoteNotificationsEnabled;
    bool appWasRated;
    
    float soundVolume;
    float musicVolume;
};

#endif /* defined(__solveMe__GameConfig__) */
