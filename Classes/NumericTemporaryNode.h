//
//  NumericTemporaryNode.h
//  urbanaria
//
//  Created by reenboog on 12.06.14.
//
//

#ifndef __urbanaria__NumericTemporaryNode__
#define __urbanaria__NumericTemporaryNode__

#include "cocos2d.h"

USING_NS_CC;

class NumericTemporaryNode: public Node {
public:
    NumericTemporaryNode();
    virtual ~NumericTemporaryNode();
    
    static NumericTemporaryNode* create();
    bool init();
    
    void setValue(int value);
    int getValue() const;
private:
    Sprite *back;
    Label *label;
    
    int value;
};

#endif /* defined(__urbanaria__NumericTemporaryNode__) */
