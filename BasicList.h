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
    BasicList(float radiusNode,
              float outlineThickness,
              size_t pointCount,
              float initAngle,
              sf::Vector2f shiftNode,
              bool doubleHeadedArrow,
              Vector<int> arr,
              std::string nameHead,
              std::string nameTail);

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

private:
    // Internal Find
    SceneNode *internalFind(const size_t index) const;
    // Internal Search
    SceneNode *internalSearch(const int val) const;
    // Clear the old array
    void clear();
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

    SceneNode *mHead, *mTail;

private:
    Vector<int> mArr;

    std::string mNameHead, mNameTail;

protected:
    int mCountNode;
};
