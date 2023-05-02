#pragma once
#include "BasicList.h"

// The function of Stack.h is combined with a ControlTable to handle Frontend
class Stack : public BasicList {
public:
    // Constructor
    Stack(Carrier &carrier);

public:
    Animation applyOperation() override;

    // Update Carrier
    void updateCarrier();

private:
    Carrier &mCarrier;
    Vector<UpdateSceneNode> mStatesHolder;
};