#pragma once
#include "BasicList.h"

// The function of DynamicArray.h is combined with a ControlTable to handle Frontend
class DynamicArray : public BasicList {
public:
    // Constructor
    DynamicArray(Carrier &carrier);
    // Destructor
    ~DynamicArray();

public:
    Animation applyOperation() override;

    // Update Carrier
    void updateCarrier();

    /* ----- Interact ----- */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
    // return SceneNode* of copy and the size
    std::pair<SceneNode*, int> createACopyOfList();

private:
    // initial initialization length
    int mStaticLength;
    // current length
    int mCurrentLength;

    SceneNode *mHeadBonus;

    Carrier &mCarrier;
    Vector<UpdateSceneNode> mStatesHolder;
};
