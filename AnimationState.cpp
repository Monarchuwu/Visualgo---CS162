#include "AnimationState.h"
#include "Constants.h"

AnimationState::AnimationState(AnimationScene scene,
                               float duration,
                               Vector<SceneNode*> deleteList)
    : mScene(scene),
      mDeleteList(deleteList),
      mDuration(),
      mCurrentPlayingAt(0),
      mIsDone(false) {
    setDuration(duration);
}

AnimationState::AnimationState(float duration)
    : mScene(),
      mDeleteList(),
      mDuration(),
      mCurrentPlayingAt(0),
      mIsDone(false) {
    setDuration(duration);
}

AnimationState::~AnimationState() { setDone(); }

void AnimationState::addUpdateSceneNode(UpdateSceneNode updateSceneNode) {
    mScene.push_back(updateSceneNode);
}

UpdateSceneNode AnimationState::popUpdateSceneNode() {
    UpdateSceneNode temp = mScene.back();
    mScene.pop_back();
    return temp;
}

void AnimationState::deleteSceneNode(SceneNode* sceneNode) {
    mDeleteList.push_back(sceneNode);
}

void AnimationState::setDuration(float duration) {
    mDuration = Constants::FramesPerSecond * (duration + 0.01f);
}
int AnimationState::getDuration() const { return mDuration; }
int AnimationState::getDurationPlayed() const { return mCurrentPlayingAt; }

void AnimationState::apply() {
    for (int i = 0; i < mScene.size(); ++i) {
        mScene[i].apply();
    }
}

void AnimationState::update(int cntFrames) {
    mCurrentPlayingAt += cntFrames;
    if (mCurrentPlayingAt > mDuration) {
        mCurrentPlayingAt = mDuration;
    }
    if (mCurrentPlayingAt == mDuration) setDone();
}

bool AnimationState::done() const { return mIsDone; }
void AnimationState::setDone() {
    mIsDone = true;
    for (int i = 0; i < mDeleteList.size(); ++i) {
        delete mDeleteList[i];
    }
}