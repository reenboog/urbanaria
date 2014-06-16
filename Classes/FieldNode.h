//
//  FieldNode.h
//  urbanaria
//
//  Created by reenboog on 12.06.14.
//
//

#ifndef __urbanaria__FieldNode__
#define __urbanaria__FieldNode__

#include "cocos2d.h"
#include "NumericPair.h"

#define kFieldMinValue 1
#define kFieldMaxValue 16

#include <vector>

USING_NS_CC;
using namespace std;

class IFieldWatcher;

class FieldNode: public Node {
public:
    enum FieldType {
        FT_Left,
        FT_Right
    };
    
    FieldNode();
    virtual ~FieldNode();
    
    static FieldNode* create(FieldType type);
    bool init(FieldType type);
    
    int applyValue(int num);
    
    int getLowerValue() const {
        return values.getLower();
    }
    
    int getHigherValue() const {
        return values.getHigher();
    }
    
    Rect getBoundingBox() const;
    
    void setHigher(int num);
    void setLower(int num);
    
    void popUp();
    void popOut();
    
    void addStateWatcher(IFieldWatcher *watcher);
private:
    Sprite *back;
    // buildings are kept in mounts' userdatas
    vector<Sprite*> buildingsMounts;
    NumericPair values;
    Node *effects;

    Sprite *numericPairMount;
    
    Sprite *higherMount;
    Label *lowerLabel;

    Sprite *lowerMount;
    Label *higherLabel;
    
    // state watchers
    vector<IFieldWatcher*> watchers;
};

#endif /* defined(__urbanaria__FieldNode__) */
