//
//  INumeric.h
//  urbanaria
//
//  Created by reenboog on 14.06.14.
//
//

#ifndef urbanaria_INumeric_h
#define urbanaria_INumeric_h

#include "cocos2d.h"

USING_NS_CC;

class NumericNode: public Node {
public:
    virtual ~NumericNode() {
        
    }
    
    NumericNode() {
        this->value = 0;
    }
    
    int getValue() const {
        return this->value;
    }
    
    virtual void setValue(int value) {
        this->value = value;
    }
private:
    int value;
};

#endif
