#pragma once
#include "BasicList.h"

// The function of Queue.h is combined with a ControlTable to handle Frontend
class Queue : public BasicList {
public:
    // Constructor
    Queue(Carrier &carrier);

public:
    Animation applyOperation();

private:
    // Update Carrier
    void updateCarrier();

private:
    Carrier &mCarrier;
    Vector<UpdateSceneNode> mStatesHolder;
};