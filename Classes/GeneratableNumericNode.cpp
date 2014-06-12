//
//  GeneratableNumericNode.cpp
//  urbanaria
//
//  Created by reenboog on 11.06.14.
//
//

#include "GeneratableNumericNode.h"

#define kBackSpriteName "generatableNumBack.png"
#define kNumFont "generatableNumFont.fnt"

#define zBack 0
#define zLabel 3

GeneratableNumericNode::GeneratableNumericNode(): Node() {
    this->back = nullptr;
    this->label = nullptr;
    
    this->value = 0;
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

void GeneratableNumericNode::setValue(int value) {
    this->value = value;
    
    label->setString(StringUtils::format("%i", this->value));
    // apply an effect may be?
    // some delegation should be applied here may be
}

int GeneratableNumericNode::getValue() const {
    return this->value;
}

