//
//  GeneratableNumericNode.cpp
//  urbanaria
//
//  Created by reenboog on 11.06.14.
//
//

#include "GeneratableNumericNode.h"
#include "IWatcher.h"

#define kBackSpriteName "generatableNumBack.png"
#define kNumFont "generatableNumFont.fnt"

#define zBack 0
#define zLabel 3

GeneratableNumericNode::GeneratableNumericNode(): NumericNode() {
    this->back = nullptr;
    this->label = nullptr;
}

GeneratableNumericNode::~GeneratableNumericNode() {
    
}

GeneratableNumericNode* GeneratableNumericNode::create() {
    GeneratableNumericNode *node = new GeneratableNumericNode();
    if(node && node->init()) {
        node->autorelease();
        return node;
    } else {
        delete node;
        node = nullptr;
        return node;
    }
}

bool GeneratableNumericNode::init() {
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

Rect GeneratableNumericNode::getBoundingBox() const {
    Rect rect = Rect(-_contentSize.width * 0.5, -_contentSize.height * 0.5, _contentSize.width, _contentSize.height);
    return RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
}

void GeneratableNumericNode::addStateWatcher(IGeneratableNumericWatcher *watcher) {
    watchers.push_back(watcher);
}

// set&get

void GeneratableNumericNode::setValue(int value) {
    NumericNode::setValue(value);
    
    if(value != 0) {
        label->setString(StringUtils::format("%i", NumericNode::getValue()));
        
        // if not zero
        for(auto w: watchers) {
            w->onValueGenerated();
        }
        // apply an effect may be if not zero?
        // some delegation should be applied then

    } else {
        label->setString(" ");
    }
}

void GeneratableNumericNode::popUp() {
    for(auto w: watchers) {
        w->onNodeTransitedIn();
    }
}

void GeneratableNumericNode::popOut() {
    for(auto w: watchers) {
        w->onNodeTransitedOut();
    }
}