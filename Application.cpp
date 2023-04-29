#include <iostream>
#include "Application.h"
#include "BasicList.h"
#include "Constants.h"

Application::Application()
    : mCarrier(),
      mWindow(),
      mList(mCarrier, Vector<int>()),
      mControlTable(mCarrier),
      mCntFrames(0),
      mAnimation() {
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

    Vector<int> SelectPosList;
    SelectPosList.push_back(Constants::Position::Beginning);
    SelectPosList.push_back(Constants::Position::Middle);
    SelectPosList.push_back(Constants::Position::End);
    mControlTable.setSelectPositionList(SelectPosList);
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
    ++mCntFrames;

    if (!mAnimation.empty()) {
        mCarrier.mPlayIsPressed = false;
        if (mCntFrames % Constants::FramesPerSecond == 0) {
            int index = mCntFrames / Constants::FramesPerSecond;
            if (index == mAnimation.size()) {
                mAnimation.clear();
            }
            else {
                for (int i = 0; i < mAnimation[index].size(); ++i) {
                    mAnimation[index][i].apply();
                }
            }
        }
    }

    if (mCarrier.mPlayIsPressed) {
        mAnimation = mList.applyOperation();
        mCntFrames = -1;
    }
}

void Application::render() {
    mWindow.clear(Constants::StandardColor[1]);
    mControlTable.draw(mWindow);
    mList.draw(mWindow);
    mWindow.display();
}
