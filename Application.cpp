#include <iostream>
#include "Application.h"
#include "BasicList.h"
#include "Constants.h"

Application::Application()
    : mWindow(),
      mList(10) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    mWindow.create(sf::VideoMode(Constants::SceneWidth, Constants::SceneHeight), "Data Structure Visualization", sf::Style::Close, settings);
    mWindow.setPosition(sf::Vector2i(10, 10));
}

void Application::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        processEvents();
        if (timeSinceLastUpdate > Constants::TimePerFrame) {
            timeSinceLastUpdate -= Constants::TimePerFrame;
            update();
        }
        render();
    }
}

void Application::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Application::update() {
}

void Application::render() {
    mWindow.clear(Constants::StandardColor[1]);
    mControlTable.draw(mWindow);
    mList.draw(mWindow);
    mWindow.display();
}
