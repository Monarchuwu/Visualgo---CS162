#pragma once
#include "AnimationState.h"

class Animation {
public:
    // Constructor
    Animation();
    Animation(Vector<AnimationState> list);

    // Add AnimationState
    void addState(AnimationState state);

    // Push Animation A to the end of this Animation
    void add(const Animation& A);
    // update the index of the List State
    void updateIndex();
    // apply all state of this animation
    void applyAll();

    // count the number of frames that this Animation is played in
    int totalFrames();
    // is this Animation done
    bool done() const;
    // is List State empty
    bool empty() const;
    // return the reference to the state at this time, no done check
    AnimationState& stateAt();
    // return the reference to the state at the end, no done check
    AnimationState& stateBack();

public:
    Vector<AnimationState> mListState;
    // the index of the State is being played
    int mIndex;

private:
    // is this Animation done
    bool mIsDone;
};
