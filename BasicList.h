#pragma once
#include <SFML/Graphics.hpp>
#include "BasicNode.h"
#include "SceneNode.h"
#include "Vector.h"
#include "Carrier.h"

class BasicList {
public:
    /* ---- Constructor ---- */
    // Constructor
    BasicList(Carrier &carrier, Vector<int> arr);

    /* ------ Modify ------ */
    size_t getCountNode() const;

    /* ----- Interact ----- */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    void updateArray(Vector<int> arr);

private:
    // Clear the old array
    void clear();
    // Set the new array
    void updateArray();
    // Set the position of HeadNode
    void updateHeadPosition();

private:
    Carrier mCarrier;

    Vector<int> mArr;

    SceneNode *mHead, *mTail;
};
