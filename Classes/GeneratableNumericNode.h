//
//  GeneratableNumericNode.h
//  urbanaria
//
//  Created by reenboog on 11.06.14.
//
//

#ifndef __urbanaria__GeneratableNumericNode__
#define __urbanaria__GeneratableNumericNode__

#include "cocos2d.h"

USING_NS_CC;

class GeneratableNumericNode: public Node {
public:
    GeneratableNumericNode();
    virtual ~GeneratableNumericNode();
    
    static GeneratableNumericNode* create();
    bool init();
    
    void setValue(int value);
    int getValue() const;
private:
    Sprite *back;
    Label *label;
    
    int value;
};

#endif /* defined(__urbanaria__GeneratableNumericNode__) */
