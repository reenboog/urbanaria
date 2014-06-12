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

#define kFieldRows 4
#define kFieldColumns 4

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
    
    this->numericPairMount = nullptr;
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
        Size backSize = back->getContentSize();
        
        for(int i = 0; i < kFieldRows; ++i) {
            for(int j = 0; j < kFieldColumns; ++j) {
                Sprite *mount = Sprite::create(buildingMountName);

                Size mountSize = mount->getContentSize();
                Size itemDisp = {(backSize.width - mountSize.width * kFieldColumns) / (kFieldColumns + 1),
                    (backSize.height - mountSize.height * kFieldRows) / (kFieldRows + 1)};
                
                Point mountPos = {mountSize.width * 0.5 + mountSize.width * (j) + itemDisp.width * (j + 1),
                    mountSize.height * 0.5 + mountSize.height * (i) + itemDisp.height * (i + 1)};
                
                //Size posVariance = {1, 1};
                //mountPos += Point(rand() % static_cast<int>(posVariance.width),
                //                  rand() % static_cast<int>(posVariance.height));
                
                mount->setPosition(mountPos);
                
                back->addChild(mount, zBuildingMount);
                
                buildingsMounts.push_back(mount);
            }
        }
        
        Point centralMountIndices = {rand() % kFieldColumns, rand() % kFieldRows};
        // mark one of the buildings as the central one
        buildingsMounts[kFieldColumns * centralMountIndices.x + centralMountIndices.y]->setTag(kCentralBuildingMountTag);

        
    }
    
    
    return true;
}