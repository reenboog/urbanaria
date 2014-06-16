//
//  NumericTemporaryNode.cpp
//  urbanaria
//
//  Created by reenboog on 12.06.14.
//
//

#include "NumericTemporaryNode.h"
#include "IWatcher.h"

#define kBackSpriteName "temporaryNumBack.png"
#define kNumFont "temporaryNumFont.fnt"

#define zBack 0
#define zLabel 3

NumericTemporaryNode::NumericTemporaryNode(): NumericNode() {
    this->back = nullptr;
    this->label = nullptr;
}

NumericTemporaryNode::~NumericTemporaryNode() {
    
}

NumericTemporaryNode* NumericTemporaryNode::create() {
    NumericTemporaryNode *node = new NumericTemporaryNode();
    if(node && node->init()) {
        node->autorelease();
        return node;
    } else {
        delete node;
        node = nullptr;
        return node;
    }
}

bool NumericTemporaryNode::init() {
    if(!NumericNode::init()) {
        return false;
    }
    
    back = Sprite::create(kBackSpriteName);
    back->setPosition({0, 0});
    
    this->addChild(back, zBack);
    this->setContentSize(back->getContentSize());
    
    label = Label::createWithBMFont(kNumFont, StringUtils::format("%i", NumericNode::getValue()));
    label->setPosition({0, 0});
    
    this->addChild(label, zLabel);
    
    return true;
}

Rect NumericTemporaryNode::getBoundingBox() const {
    Rect rect = Rect(-_contentSize.width * 0.5, -_contentSize.height * 0.5, _contentSize.width, _contentSize.height);
    return RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
}

// set&get

void NumericTemporaryNode::addStateWatcher(ITemporaryNumericWatcher *watcher) {
    watchers.push_back(watcher);
}

void NumericTemporaryNode::setValue(int value) {
    NumericNode::setValue(value);
    
    if(value != 0) {
        label->setString(StringUtils::format("%i", NumericNode::getValue()));
        // apply an effect may be?
        // some delegation should be applied here may be
        
        // if not zero
        for(auto w: watchers) {
            w->onValueCached();
        }
    } else {
        label->setString(" ");
    }
    
}
