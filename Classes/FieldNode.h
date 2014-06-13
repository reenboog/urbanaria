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

#include <vector>

USING_NS_CC;
using namespace std;

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
    
    bool applyValue(int num);
    
    int getLowerValue() const {
        return values.getLower();
    }
    
    int getHigherValue() const {
        return values.getHigher();
    }
    
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
};

#endif /* defined(__urbanaria__FieldNode__) */