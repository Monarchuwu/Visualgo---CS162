#pragma once
#include <SFML/Graphics.hpp>
#include "BasicNode.h"
#include "SceneNode.h"
#include "Vector.h"
#include "Carrier.h"
#include "AnimationBuilder.h"

class BasicList {
public:
    /* ---- Constructor ---- */
    // Constructor
    BasicList(Carrier &carrier, Vector<int> arr);

    /* ------ Modify ------ */
    // return the number of Node
    size_t getCountNode() const;
    // insert new Node before Node ptr
    void insertNodeBefore(SceneNode *ptr, int val);
    // delete Node ptr
    void deleteNode(SceneNode *ptr);

    /* ------ Search & Find ------ */
    // Find
    SceneNode *find(const size_t index) const;
    // Search
    SceneNode *search(const int val) const;

    /* ----- Interact ----- */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    void updateArray(Vector<int> arr);
    Animation applyOperation();

private:
    // Internal Find
    SceneNode *internalFind(const size_t index) const;
    // Internal Search
    SceneNode *internalSearch(const int val) const;
    // Clear the old array
    void clear();
    // Set the new array
    void updateArray();
    // Set the position of HeadNode
    void updateHeadPosition();
    // Update Carrier
    void updateCarrier();

private:
    Carrier &mCarrier;

    Vector<int> mArr;
    int mCountNode;

    SceneNode *mHead, *mTail;

    Vector<UpdateSceneNode> mStatesHolder;
};
