//
//  NumericTemporaryNode.cpp
//  urbanaria
//
//  Created by reenboog on 12.06.14.
//
//

#include "NumericTemporaryNode.h"

#define kBackSpriteName "temporaryNumBack.png"
#define kNumFont "temporaryNumFont.fnt"

#define zBack 0
#define zLabel 3

NumericTemporaryNode::NumericTemporaryNode(): Node() {
    this->back = nullptr;
    this->label = nullptr;
    
    this->value = 0;
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
    if(!Node::init()) {
        return false;
    }
    
    back = Sprite::create(kBackSpriteName);
    back->setPosition({0, 0});
    
    this->addChild(back, zBack);
    this->setContentSize(back->getContentSize());
    
    label = Label::createWithBMFont(kNumFont, StringUtils::format("%i", this->value));
    label->setPosition({0, 0});
    
    this->addChild(label, zLabel);
    
    return true;
}

// set&get

void NumericTemporaryNode::setValue(int value) {
    this->value = value;
    
    label->setString(StringUtils::format("%i", this->value));
    // apply an effect may be?
    // some delegation should be applied here may be
}

int NumericTemporaryNode::getValue() const {
    return this->value;
}