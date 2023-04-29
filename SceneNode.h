#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "BasicNode.h"

class SceneNode : public sf::Transformable {
public:
    /* ---- Constructor ---- */
    // Constructor
    SceneNode();

    /* ------ Modify ------ */
    // Attach a SceneNode as a child
    void attachChild(SceneNode* child);
    // Detach a child
    // Return pointer to that child
    SceneNode* detachChild(const SceneNode& node);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    BasicNode mNode;

private:
    Vector<SceneNode*> mChildren;
    SceneNode* mParent;
};
