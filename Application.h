#pragma once
#include <SFML/Graphics.hpp>
#include "BasicList.h"

class Application {
public:
    Application();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    sf::RenderWindow mWindow;
    BasicList mList;
};