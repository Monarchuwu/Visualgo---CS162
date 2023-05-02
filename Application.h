#pragma once
#include <SFML/Graphics.hpp>
#include "ControlTable.h"
#include "Carrier.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "DataStructureButtonBlock.h"

class Application {
public:
    Application();

    void setDataStructure(int dataStructure);

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
    Queue mQueue;
    Stack mStack;
    ControlTable mControlTable;

    Animation mAnimation;

    int mDataStructure;
    DataStructureButtonBlock mDSButtonBlock;
};