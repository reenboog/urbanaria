//
//  FieldNode.cpp
//  urbanaria
//
//  Created by reenboog on 12.06.14.
//
//

#include "FieldNode.h"

#define kLeftFieldBackName "leftFieldBack.png"
#define kRightFieldBackName "rightFieldBack.png"

#define kLeftFieldBuildingMountName "leftFieldBuildingMount.png"
#define kRightFieldBuildingMountName "rightFieldBuildingMount.png"

// IMPORTANT: number of buildings
#define kNumOfBuildings 5
//

#define kBuildingPrefix "building"
#define kRandomBuildingName()(StringUtils::format("%s%i.png",  kBuildingPrefix, rand() % kNumOfBuildings))

#define zBack 0
#define zBuildingMount 0

#define kCentralBuildingMountTag 113

FieldNode::~FieldNode() {
}

FieldNode::FieldNode(): Node() {
    //vector<Sprite*> buildingsMounts;
    
    this->back = nullptr;
    
    this->effects = nullptr;
    
    this->numericMount = nullptr;
    this->lowerLabel = nullptr;
    this->higherLabel = nullptr;
}

FieldNode* FieldNode::create(FieldType type) {
    FieldNode *node = new FieldNode();
    if(node && node->init(type)) {
        node->autorelease();
        return node;
    } else {
        delete node;
        node = nullptr;
        return node;
    }
}

bool FieldNode::init(FieldType type) {
    if(!Node::init()) {
        return false;
    }
    
    // assume FT_Left as a default field type
    string backName = kLeftFieldBackName;
    string buildingMountName = kLeftFieldBuildingMountName;
    
    switch(type) {
        case FT_Left: break;
        case FT_Right:
            backName = kRightFieldBackName;
            buildingMountName = kRightFieldBuildingMountName;
            break;
        default:
            CCLOG("Field type unrecognized. Type: %i", static_cast<int>(type));
            return false;
    }
    
    {
        // back
        back = Sprite::create(backName);
        back->setPosition({0, 0});
        
        this->addChild(back, zBack);
        this->setContentSize(back->getContentSize());
    }
    
    {
        // mounts
        
    }
    
    
    return true;
}