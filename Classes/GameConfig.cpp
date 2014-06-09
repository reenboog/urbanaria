//
//  GameConfig.cpp
//  solveMe
//
//  Created by Alex Gievsky on 11.11.13.
//
//

#include "GameConfig.h"
#include "Constants.h"
#include "Shared.h"
#include "Localized.h"

#include "rapidjson/document.h"

#include <string>

using namespace std;

#define kHintsLeftKey "hintsLeft"
#define kFirstPuzzleIndexKey "firstPuzzleIndex"
#define kSoundVolumeKey "soundVolumeKey"
#define kMusicVolumeKey "musicVolumeKey"
#define kRemoteNotificationsEnabledKey "remoteNotificationsEnabledKey"
#define kAppWasRatedKey "appWasRatedKey"
#define kRateBadgeWasShownKey "rateBadgeWasShownKey"

#define kRateUsNotification "rateUsNotificationKey"
#define kFirstPuzzleIndex 0

GameConfig * GameConfig::__sharedInstance = nullptr;


GameConfig::~GameConfig() {
    
}

GameConfig::GameConfig() {
    
}

GameConfig * GameConfig::sharedInstance() {
    if(__sharedInstance == nullptr) {
        __sharedInstance = new GameConfig();
    }
    
    return __sharedInstance;
}

void GameConfig::purge() {
    delete __sharedInstance;
    __sharedInstance = nullptr;
    
    FileUtils::getInstance()->destroyInstance();
}

void GameConfig::load() {
    soundVolume = UserDefault::getInstance()->getFloatForKey(kSoundVolumeKey, 0.8f);
    musicVolume = UserDefault::getInstance()->getFloatForKey(kMusicVolumeKey, 0.7f);
    
    remoteNotificationsEnabled = UserDefault::getInstance()->getBoolForKey(kRemoteNotificationsEnabledKey, false);
    appWasRated = UserDefault::getInstance()->getBoolForKey(kAppWasRatedKey, false);
    rateBadgeWasAlreadyShown = UserDefault::getInstance()->getBoolForKey(kRateUsNotification, false);
}

void GameConfig::save() {
    // use user defaults here
    UserDefault::getInstance()->setFloatForKey(kMusicVolumeKey, musicVolume);
    UserDefault::getInstance()->setFloatForKey(kSoundVolumeKey, soundVolume);
    UserDefault::getInstance()->setBoolForKey(kRemoteNotificationsEnabledKey, remoteNotificationsEnabled);
    UserDefault::getInstance()->setBoolForKey(kAppWasRatedKey, appWasRated);
    UserDefault::getInstance()->setBoolForKey(kRateUsNotification, rateBadgeWasAlreadyShown);
}

void GameConfig::loadFilePaths() {
    // load file paths
    ssize_t configDataSize = 0;
    unsigned char *t = (FileUtils::getInstance()->getFileData("Res/config.json", "r", &configDataSize));
    
    char *configData = new char[configDataSize + 1];
    memcpy(configData, t, configDataSize);
    configData[configDataSize] = NULL;
    
    delete[] t;
    t = NULL;
    
    
    LanguageType currentLanguage = Application::getInstance()->getCurrentLanguage();
    
    string languagePrefix = Localized::languageShortNameForType(currentLanguage);
    
    auto addResourcePath = [=](const string &path) {
        FileUtils::getInstance()->addSearchPath((path + languagePrefix).c_str());
        FileUtils::getInstance()->addSearchPath(path.c_str());
    };
    
    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    
    rapidjson::Document configDoc;
    configDoc.Parse<0>(configData);
    
    string layoutBaseDimensionType = configDoc["layoutBaseDimension"].GetString();
    
    float frameBaseDimension = frameSize.height;
    
    if(layoutBaseDimensionType.compare("width") == 0) {
        frameBaseDimension = frameSize.width;
    }

    const auto &designEntriesArray = configDoc["designResolutionEntries"];
    if(designEntriesArray.IsArray()) {
        for(int i = designEntriesArray.Size() - 1; i >= 0; --i) {
            const auto &currentDeviceEntry = designEntriesArray[i];
            
            if(currentDeviceEntry.IsObject()) {
                double currentResolutionBaseDimension = currentDeviceEntry[layoutBaseDimensionType.c_str()].GetDouble();
                
                if(frameBaseDimension > currentResolutionBaseDimension) {
                    int requiredEntryIndex = MIN(i + 1, designEntriesArray.Size() - 1);
                    const auto &requiredEntry = designEntriesArray[requiredEntryIndex];
                    double requiredBaseDimension = requiredEntry[layoutBaseDimensionType.c_str()].GetDouble();
                    
                    //
                    double layoutWidth = requiredEntry["designWidth"].GetDouble();
                    double layoutHeight = requiredEntry["designHeight"].GetDouble();
                    
                    this->setDesignLayoutSize({layoutWidth, layoutHeight});
                    
                    float designLayoutBaseDimension = layoutHeight;
                    ResolutionPolicy policy = ResolutionPolicy::FIXED_HEIGHT;
                    
                    if(layoutBaseDimensionType.compare("width") == 0) {
                        designLayoutBaseDimension = layoutWidth;
                        //frameBaseDimension = frameSize.width;
                        policy = ResolutionPolicy::FIXED_WIDTH;
                    }
                    
                    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(layoutWidth, layoutHeight, policy);
                    Director::getInstance()->setContentScaleFactor(requiredBaseDimension / designLayoutBaseDimension);
                    
                    Size visibleSize = Director::getInstance()->getVisibleSize();
                    this->setVisibleOrigin({(visibleSize.width - layoutWidth) / 2.0, (visibleSize.height - layoutHeight) / 2.0});
                    //

                    // load required entry and all the entries above
                    for(; requiredEntryIndex >= 0; --requiredEntryIndex) {
                        const auto &entryToLoad = designEntriesArray[requiredEntryIndex];
                        
                        if(entryToLoad.IsObject()) {
                            for(auto it = entryToLoad["paths"].Begin(); it != entryToLoad["paths"].End(); ++it) {
                                string path = it->GetString();
                                addResourcePath(path);
                            }
                        }
                    }
                    
                    // stop iterating all the rest entries
                    break;
                }
            }
        }
    }

    // load shared paths
    
    const auto &sharedPathsArray = configDoc["sharedPaths"];
    if(sharedPathsArray.IsArray()) {
        for(auto it = sharedPathsArray.Begin(); it != sharedPathsArray.End(); ++it) {
            string path = it->GetString();
            addResourcePath(path);
        }
    }
    
    delete[] configData;
}

Size GameConfig::getDesignLayoutSize() {
    return this->designLayoutSize;
}

Point GameConfig::getVisibleOrigin() {
    return this->visibleOrigin;
}

void GameConfig::setDesignLayoutSize(const Size &size) {
    this->designLayoutSize = size;
}

void GameConfig::setVisibleOrigin(const Point &point) {
    this->visibleOrigin = point;
}

bool GameConfig::areRemoteNotificationsEnabled() {
    return remoteNotificationsEnabled;
}

void GameConfig::setRemoteNotificationsEnabled(bool enabled) {
    this->remoteNotificationsEnabled = enabled;
}

bool GameConfig::isAppAlreadyRated() {
    return this->appWasRated;
}

void GameConfig::setAppRated(bool rated) {
    this->appWasRated = rated;
}

bool GameConfig::wasRateBadgeAlreadyShown() {
    return this->rateBadgeWasAlreadyShown;
}

void GameConfig::setRateBadgeAlreadyShown(bool shown) {
    this->rateBadgeWasAlreadyShown = true;
}

void GameConfig::setMusicVolume(float volume) {
    this->musicVolume = volume;
}

float GameConfig::getMusicVolume() {
    return this->musicVolume;
}

void GameConfig::setSoundVolume(float volume) {
    this->soundVolume = volume;
}

float GameConfig::getSoundVolume() {
    return this->soundVolume;
}
