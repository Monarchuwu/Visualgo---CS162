#pragma once
#include <SFML/Graphics.hpp>
#include "BasicList.h"
#include "ControlTable.h"
#include "Carrier.h"
#include "SinglyLinkedList.h"

class Application {
public:
    Application();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    Carrier mCarrier;

    sf::RenderWindow mWindow;
    SinglyLinkedList mList;
    ControlTable mControlTable;

    Animation mAnimation;
};