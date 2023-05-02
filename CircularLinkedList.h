#pragma once
#include "BasicList.h"

// The function of CircularLinkedList.h is combined with a ControlTable to handle Frontend
class CircularLinkedList : public BasicList {
public:
    // Constructor
    CircularLinkedList(Carrier &carrier);

public:
    Animation applyOperation();

    // Update Carrier
    void updateCarrier();

    /* ----- Interact ----- */
    //virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
    Carrier &mCarrier;
    Vector<UpdateSceneNode> mStatesHolder;
};

//void CircularLinkedList::draw(sf::RenderTarget &target, sf::RenderStates states) {
//    // BasicList::draw(target, states);
//}
