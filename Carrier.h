#pragma once
#include "Vector.h"

// Communication method between elements in Application
class Carrier {
public:
    Carrier();

public:
    // List
    int mCountNode;
    // ControlTable
    int mOperationType;
    Vector<int> mArr;
    int mPos;
    int mVal;
    bool mPlayIsPressed;
    bool mAnimationIsPlaying;
};
