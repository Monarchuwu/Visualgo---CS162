#pragma once
#include "UpdateSceneNode.h"
#include "SceneNode.h"

typedef Vector<UpdateSceneNode> AnimationScene;

class AnimationState {
public:
    // Constructor
    AnimationState(AnimationScene scene,
                   float duration                = 1.f,
                   Vector<SceneNode*> deleteList = Vector<SceneNode*>());
    // Constructor
    AnimationState(float duration = 1.f);
    // Destructor
    ~AnimationState();

    // Add UpdateSceneNode
    void addUpdateSceneNode(UpdateSceneNode updateSceneNode);
    // Delete UpdateSceneNode at the end of the list
    UpdateSceneNode popUpdateSceneNode();
    // delete SceneNode when this scene has done
    void deleteSceneNode(SceneNode* sceneNode);
    // set the time that this scene is played in
    void setDuration(float duration);
    // get the number of frames that this scene is played in
    int getDuration() const;
    // get the number of frames that this scene played
    int getDurationPlayed() const;

    // apply the scene update
    void apply();
    // update the number of frames this scene played
    void update(int cntFrames = 1);
    // is this scene done
    bool done() const;

private:
    void setDone();

public:
    AnimationScene mScene;
    // List SceneNodes have to delete after this scene
    Vector<SceneNode*> mDeleteList;

    // the number of frames that this scene is played in
    int mDuration;
    // the amount of frames this scene played
    int mCurrentPlayingAt;

private:
    // this scene is done
    bool mIsDone;
};
