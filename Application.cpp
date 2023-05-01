#include <iostream>
#include "Application.h"
#include "BasicList.h"
#include "Constants.h"

/*
      mList(Constants::CirleNodeRadius,
           Constants::NodeOutlineThinkness,
           30, 0,
           //4, Constants::pi / 4,
           Constants::ShiftNode,
           //sf::Vector2f(Constants::CirleNodeRadius * 1.405f + Constants::NodeOutlineThinkness * 2, 0),
           true,
           mCarrier, Vector<int>()),
*/

Application::Application()
    : mCarrier(),
      mWindow(),
      mSLL(mCarrier),
      mDLL(mCarrier),
      mControlTable(mCarrier),
      mAnimation(),
      mDataStructure(0) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    mWindow.create(sf::VideoMode(Constants::SceneWidth, Constants::SceneHeight), "Data Structure Visualization", sf::Style::Close, settings);
    mWindow.setPosition(sf::Vector2i(10, 10));

    Vector<int> nameButtonMain;
    nameButtonMain.push_back(Constants::Operation::Init);
    nameButtonMain.push_back(Constants::Operation::Insert);
    nameButtonMain.push_back(Constants::Operation::Delete);
    nameButtonMain.push_back(Constants::Operation::Update);
    nameButtonMain.push_back(Constants::Operation::Search);
    mControlTable.setButtonMainList(nameButtonMain);
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
    while (!mAnimation.done() && mAnimation.stateAt().done()) {
        mAnimation.updateIndex();
    }

    // the play button is pressed
    if (mCarrier.mPlayIsPressed) {
        mAnimation.applyAll();
        switch (mDataStructure) {
            case DataStructure::SLL:
                mAnimation = mSLL.applyOperation();
                break;

            case DataStructure::DLL:
                mAnimation = mDLL.applyOperation();
                break;

            default:
                break;
        }
    }

    // play animation
    while (!mAnimation.done() && mAnimation.stateAt().done()) {
        mAnimation.updateIndex();
    }
    if (!mAnimation.done()) {
        if (mAnimation.stateAt().getDurationPlayed() == 0) {
            mAnimation.stateAt().apply();
        }
        mAnimation.stateAt().update(1);
    }
}

void Application::render() {
    mWindow.clear(Constants::StandardColor[1]);
    mControlTable.draw(mWindow);
    switch (mDataStructure) {
        case DataStructure::SLL:
            mSLL.draw(mWindow);
            break;

        case DataStructure::DLL:
            mDLL.draw(mWindow);
            break;

        default:
            break;
    }
    mWindow.display();
}
