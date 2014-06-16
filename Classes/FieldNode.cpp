//
//  FieldNode.cpp
//  urbanaria
//
//  Created by reenboog on 12.06.14.
//
//

#include "FieldNode.h"
#include "IWatcher.h"

#define kLeftFieldBackName "leftFieldBack.png"
#define kRightFieldBackName "rightFieldBack.png"

#define kLeftFieldBuildingMountName "leftFieldBuildingMount.png"
#define kRightFieldBuildingMountName "rightFieldBuildingMount.png"

#define kLeftNumericMountName "leftFieldNumericMount.png"
#define kRightNumericMountName "rightFieldNumericMount.png"

#define kLeftFieldHigherNumericMount "leftFieldHigherNumericMount.png"
#define kRightFieldHigherNumericMount "rightFieldHigherNumericMount.png"

#define kLeftFieldLowerNumericMount "leftFieldLowerNumericMount.png"
#define kRightFieldLowerNumericMount "rightFieldLowerNumericMount.png"

#define kHigherNumericFont "higherNumericFont.fnt"
#define kLowerNumericFont "lowerNumericFont.fnt"

#define kFieldRows 4
#define kFieldColumns 4

// IMPORTANT: number of buildings
#define kNumOfBuildings 5
//

#define kBuildingPrefix "building"
#define kRandomBuildingName()(StringUtils::format("%s%i.png",  kBuildingPrefix, rand() % kNumOfBuildings))

#define zBack 0
#define zBuildingMount 0
#define zNumericMount -1

#define kCentralBuildingMountTag 113

FieldNode::~FieldNode() {
}

FieldNode::FieldNode(): Node() {
    //vector<Sprite*> buildingsMounts;
    
    this->back = nullptr;
    
    this->effects = nullptr;
    
    this->numericPairMount = nullptr;

    this->lowerLabel = nullptr;
    this->lowerMount = nullptr;
    
    this->higherLabel = nullptr;
    this->higherMount = nullptr;
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
    string numericMountName = kLeftNumericMountName;
    string higherNumericName = kLeftFieldHigherNumericMount;
    string lowerNumericName = kLeftFieldLowerNumericMount;
    
    Point numericMountRelativePos = {1.045 * 0.5, -0.7 * 0.5};
    Point higherNumericRelativePos = {0.56, 0.63};
    Point lowerNumericRelativePos = {0.56, 0.27};
    
    switch(type) {
        case FT_Left: break;
        case FT_Right:
            backName = kRightFieldBackName;
            buildingMountName = kRightFieldBuildingMountName;
            numericMountName = kRightNumericMountName;
            higherNumericName = kRightFieldHigherNumericMount;
            lowerNumericName = kRightFieldLowerNumericMount;
            
            numericMountRelativePos = Point(-1.09 * 0.5, 0.7 * 0.48);
            higherNumericRelativePos = Point(0.5, 0.67);
            lowerNumericRelativePos = Point(0.5, 0.27);
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
        // numeric nodes
        numericPairMount = Sprite::create(numericMountName);
        numericPairMount->setPosition({numericMountRelativePos.x * back->getContentSize().width,
                                        numericMountRelativePos.y * back->getContentSize().height});
        
        this->addChild(numericPairMount, zNumericMount);
        
        higherMount = Sprite::create(higherNumericName);
        higherMount->setPosition({numericPairMount->getContentSize().width * higherNumericRelativePos.x,
                                    numericPairMount->getContentSize().height * higherNumericRelativePos.y});
        
        numericPairMount->addChild(higherMount);
        
        lowerMount = Sprite::create(lowerNumericName);
        lowerMount->setPosition({numericPairMount->getContentSize().width * lowerNumericRelativePos.x,
                                    numericPairMount->getContentSize().height * lowerNumericRelativePos.y});
        
        numericPairMount->addChild(lowerMount);
        
        // numeric labels
        higherLabel = Label::createWithBMFont(kHigherNumericFont, "10");
        higherLabel->setPosition({higherMount->getContentSize().width * 0.5, higherMount->getContentSize().height * 0.5});
        
        higherMount->addChild(higherLabel);
        
        lowerLabel = Label::createWithBMFont(kLowerNumericFont, "2");
        lowerLabel->setPosition({lowerMount->getContentSize().width * 0.5, lowerMount->getContentSize().height * 0.5});
        
        lowerMount->addChild(lowerLabel);
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
                mount->setUserData(nullptr);
                
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

Rect FieldNode::getBoundingBox() const {
    Rect rect = Rect(-_contentSize.width * 0.5, -_contentSize.height * 0.5, _contentSize.width, _contentSize.height);
    return RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
}

void FieldNode::setHigher(int num) {
    values.setHigher(num);
    
    higherLabel->setString(StringUtils::format("%i", num));
}

void FieldNode::setLower(int num) {
    values.setLower(num);
    
    lowerLabel->setString(StringUtils::format("%i", num));
}

int FieldNode::applyValue(int num) {
    int result = values.apply(num);
    
    this->values.setHigher(max(kFieldMinValue, this->values.getHigher()));
    
    higherLabel->setString(StringUtils::format("%i", values.getHigher()));
    lowerLabel->setString(StringUtils::format("%i", values.getLower()));
    
    // apply labels
    // build/destroy a building maybe
    // apply some animatins here
    // broadcast the result to all the observers if any
    
    for(IFieldWatcher *w: watchers) {
        w->onValuesApplied(result);
    }
    
    return result;
}

// animations


void FieldNode::addStateWatcher(IFieldWatcher *watcher) {
    watchers.push_back(watcher);
}

void FieldNode::popUp() {
//    // run some animations the broadcast a result
//    for(IFieldWatcher *w: watchers) {
//        w->onFieldTransitedIn();
//    }
}

void FieldNode::popOut() {
//    // run some animations the broadcast a result
//    for(IFieldWatcher *w: watchers) {
//        w->onFieldTransitedOut();
//    }
}