#pragma once
#include <SFML/Graphics.hpp>
#include "BasicList.h"
#include "ControlTable.h"
#include "Carrier.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

class Application {
    enum DataStructure {
        SLL,
        DLL,
        CLL,
        Stack,
        Queue,
        StaticArr,
        DynamicArr,
    };
    int mDataStructure;

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
    SinglyLinkedList mSLL;
    DoublyLinkedList mDLL;
    ControlTable mControlTable;

    Animation mAnimation;
};