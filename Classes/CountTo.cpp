//
//  CountTo.cpp
//  old28
//
//  Created by reenboog on 24.12.13.
//
//

#include "CountTo.h"

CountTo* CountTo::create(float duration, int endValue, int startValue, string formatter) {
    CountTo *p = new CountTo();
    if(p && p->init(duration, endValue, startValue, formatter)) {
        p->autorelease();
        return p;
    } else {
        delete p;
        return nullptr;
    }
}

bool CountTo::init(float duration, int endValue, int startValue, string formatter) {
    if(ActionInterval::initWithDuration(duration)) {
        this->endValue = endValue;
        this->startValue = startValue;
        this->formatter = formatter;
        
        return true;
    }
    
    return false;
}

CountTo* CountTo::clone(void) const {
	CountTo *p = new CountTo();
    p->init(this->getDuration(), this->endValue, this->startValue, this->formatter);
	p->autorelease();
	return p;
}

void CountTo::startWithTarget(Node *target) {
    ActionInterval::startWithTarget(target);
    this->valueDelta = this->endValue - this->startValue;
}

CountTo* CountTo::reverse() const {
    return CountTo::create(this->getDuration(), this->startValue, this->endValue, this->formatter);
}

void CountTo::update(float t) {
    Label *label = static_cast<Label*>(this->getTarget());
    
    int value = this->startValue + this->valueDelta * t;
    label->setString(StringUtils::format(this->formatter.c_str(), value));
}