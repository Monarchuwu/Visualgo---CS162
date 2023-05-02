#pragma once
#include <SFML/Graphics.hpp>
#include "BasicNode.h"
#include "SceneNode.h"
#include "Vector.h"
#include "Carrier.h"
#include "Animation.h"
#include "AnimationBuilder.h"

class BasicList {
public:
    /* ---- Constructor ---- */
    // Constructor
    BasicList(float radiusNode,
              float outlineThickness,
              size_t pointCount,
              float initAngle,
              sf::Vector2f shiftNode,
              bool doubleHeadedArrow,
              Vector<int> arr);

    /* ------ Modify ------ */
    // return the number of Node
    size_t getCountNode() const;

    /* ------ Search & Find ------ */
    // Find
    SceneNode *find(const size_t index) const;
    // Search
    SceneNode *search(const int val) const;

    /* ----- Interact ----- */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    void updateArray(Vector<int> arr);
    // Set the position of HeadNode
    void updateHeadPosition();
    // Set the Text Below the Node
    void updateTextBelow();

    virtual Animation applyOperation() = 0;

private:
    // Internal Find
    SceneNode *internalFind(const size_t index) const;
    // Internal Search
    SceneNode *internalSearch(const int val) const;
    // Clear the old array
    void clear();
    // Clear TextBelow of all node
    void clearTextBelow();
    // Set the new array
    void updateArray();

protected:
    // init for BasicNode

    float mRadiusNode;
    float mOutlineThicknessNode;
    size_t mPointCountNode;
    float mInitAngleNode;
    sf::Vector2f mShiftNode;
    bool mDoubleHeadedArrow;

    SceneNode *mHead;

private:
    Vector<int> mArr;

protected:
    int mCountNode;
};
