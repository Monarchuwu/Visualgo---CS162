#include <iostream>
#include "Application.h"
#include "BasicList.h"
#include "Constants.h"

Application::Application()
    : mWindow(),
      mList(Constants::MaxCountNode) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    mWindow.create(sf::VideoMode(Constants::SceneWidth, Constants::SceneHeight), "Data Structure Visualization", sf::Style::Close, settings);
    mWindow.setPosition(sf::Vector2i(10, 10));

    Constants::CountNode = mList.getCountNode();
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
            case sf::Event::MouseButtonPressed:
                mControlTable.handleButtonInput(event.mouseButton, true);
                break;

            case sf::Event::MouseButtonReleased:
                mControlTable.handleButtonInput(event.mouseButton, false);
                break;

            case sf::Event::KeyReleased:
                mControlTable.handleKeyInput(event.key);
                break;

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
