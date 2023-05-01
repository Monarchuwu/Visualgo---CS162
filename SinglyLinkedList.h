#pragma once
#include "BasicList.h"

// The function of SLL.h is combined with a ControlTable to handle Frontend
class SinglyLinkedList : public BasicList {
public:
    // Constructor
    SinglyLinkedList(Carrier &carrier);

public:
    Animation applyOperation();

private:
    // Update Carrier
    void updateCarrier();

private:
    Carrier &mCarrier;
    Vector<UpdateSceneNode> mStatesHolder;
};
