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
#include "NumericNode.h"
#include <vector>

USING_NS_CC;
using namespace std;

class IGeneratableNumericWatcher;

class GeneratableNumericNode: public NumericNode {
public:
    GeneratableNumericNode();
    virtual ~GeneratableNumericNode();
    
    static GeneratableNumericNode* create();
    bool init();
    
    Rect getBoundingBox() const;
    
    void setValue(int value);
    
    void popUp();
    void popOut();
    
    void addStateWatcher(IGeneratableNumericWatcher *watcher);
private:
    Sprite *back;
    Label *label;
    
    vector<IGeneratableNumericWatcher*> watchers;
};

#endif /* defined(__urbanaria__GeneratableNumericNode__) */
