#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "BasicNode.h"

class SceneNode : public sf::Transformable {
public:
    /* ---- Constructor ---- */
    // Constructor
    SceneNode(BasicNode node, bool arrowVisible = true);
    // Destructor
    ~SceneNode();

    /* ------ Modify ------ */
    // Attach a SceneNode as a child
    void attachChild(SceneNode* child);
    // Detach a child
    // Return pointer to that child
    SceneNode* detachChild(const SceneNode& node);

    /* ------- Arrow ------- */
    void enableArrow();
    void disableArrow();

    /* ----- Interact ----- */
    // Draw SceneTree on target with states
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawArrow(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    /* ----- Interact ----- */
    // Draw SceneNode on target with states
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    BasicNode mNode;
    bool mArrowVisible;

    // they should be private, but i have to do this to access mChildren...
    Vector<SceneNode*> mChildren;
    SceneNode* mParent;
};
