#pragma once
#include "BasicList.h"

// The function of DLL.h is combined with a ControlTable to handle Frontend
class DoublyLinkedList : public BasicList {
public:
    // Constructor
    DoublyLinkedList(Carrier &carrier);

public:
    Animation applyOperation();

    // Update Carrier
    void updateCarrier();

private:
    Carrier &mCarrier;
    Vector<UpdateSceneNode> mStatesHolder;
};
