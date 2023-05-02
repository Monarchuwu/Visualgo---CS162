#pragma once
#include "BasicList.h"

// The function of DynamicArray.h is combined with a ControlTable to handle Frontend
class DynamicArray : public BasicList {
public:
    // Constructor
    DynamicArray(Carrier &carrier);

public:
    Animation applyOperation() override;

    // Update Carrier
    void updateCarrier();

private:
    // initial initialization length
    int mStaticLength;
    // current length
    int mCurrentLength;

    Carrier &mCarrier;
    Vector<UpdateSceneNode> mStatesHolder;
};
