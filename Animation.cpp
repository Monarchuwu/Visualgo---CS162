#include "Animation.h"

Animation::Animation()
    : mListState(),
      mIndex(0),
      mIsDone(false) {
}

void Animation::addState(AnimationState state) {
    mListState.push_back(state);
}

void Animation::add(const Animation& A) {
    for (int i = 0; i < A.mListState.size(); ++i) {
        addState(A.mListState[i]);
    }
}

void Animation::updateIndex() {
    ++mIndex;
    if (mIndex == mListState.size()) mIsDone = true;
}

void Animation::applyAll() {
    while (!done()) {
        if (!stateAt().done() && stateAt().getDurationPlayed() == 0) {
            stateAt().apply();
        }
        updateIndex();
    }
}

int Animation::totalFrames() {
    int cntFrames = 0;
    for (int i = 0; i < mListState.size(); ++i) {
        cntFrames += mListState[i].getDuration();
    }
    return cntFrames;
}

bool Animation::done() const { return empty() || mIsDone; }
bool Animation::empty() const { return mListState.empty(); }

AnimationState& Animation::stateAt() {
    return mListState[mIndex];
}
AnimationState& Animation::stateBack() {
    return mListState.back();
}
