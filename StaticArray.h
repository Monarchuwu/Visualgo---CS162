#pragma once
#include "BasicList.h"

// The function of StaticArray.h is combined with a ControlTable to handle Frontend
class StaticArray : public BasicList {
public:
    // Constructor
    StaticArray(Carrier &carrier);

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
