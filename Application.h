#pragma once
#include <SFML/Graphics.hpp>
#include "BasicList.h"
#include "ControlTable.h"
#include "Carrier.h"

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
    BasicList mList;
    ControlTable mControlTable;

    int mCntFrames;
    Animation mAnimation;
};