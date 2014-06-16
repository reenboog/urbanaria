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
#include "NumericNode.h"
#include <vector>

USING_NS_CC;
using namespace std;

class ITemporaryNumericWatcher;

class NumericTemporaryNode: public NumericNode {
public:
    NumericTemporaryNode();
    virtual ~NumericTemporaryNode();
    
    static NumericTemporaryNode* create();
    bool init();
    
    Rect getBoundingBox() const;
    
    void setValue(int value);
    
    void addStateWatcher(ITemporaryNumericWatcher *watcher);
private:
    Sprite *back;
    Label *label;
    
    vector<ITemporaryNumericWatcher*> watchers;
};

#endif /* defined(__urbanaria__NumericTemporaryNode__) */
