//
//  CountTo.h
//  old28
//
//  Created by reenboog on 24.12.13.
//
//

#ifndef __old28__CountTo__
#define __old28__CountTo__

#include "cocos2d.h"
#include <string>

using namespace std;

USING_NS_CC;

class CountTo: public ActionInterval {
public:
    static CountTo* create(float duration, int endValue, int startValue, string formatter);
    bool init(float duration, int endValue, int startValue, string formatter);
    
    virtual CountTo* clone() const;
    virtual CountTo* reverse() const;
    
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
private:
    float startValue;
    float valueDelta;
    
    string formatter;
    
    int endValue;
};

#endif /* defined(__old28__CountTo__) */
