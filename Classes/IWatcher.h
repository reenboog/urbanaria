//
//  IFieldWatcher.h
//  urbanaria
//
//  Created by reenboog on 14.06.14.
//
//

#ifndef urbanaria_IFieldWatcher_h
#define urbanaria_IFieldWatcher_h

class IFieldWatcher {
public:
    virtual void onValuesApplied(int valueDiff) = 0;
};

class IGeneratableNumericWatcher {
public:
    virtual void onNodeTransitedIn() = 0;
    virtual void onNodeTransitedOut() = 0;
    virtual void onValueGenerated() = 0;
};

class ITemporaryNumericWatcher {
public:
    virtual void onValueCached() = 0;
};

#endif
