#include "SelectPositionBlock.h"
#include "Constants.h"

SelectPositionBlock::SelectPositionBlock(float width,
                                         float height,
                                         sf::Vector2f position)
    : mBoxText(),
      mTriangleLeft(),
      mTriangleRight(),
      mWidth(width),
      mHeight(height),
      mPosition(position) {
    mBoxText.setFillColor(Constants::BackGroundTextColor);
    mBoxText.setFont(Constants::Font);
    mBoxText.setStyle(sf::Text::Bold);
    mBoxText.setCharacterSize(Constants::ButtonMainCharacterSize);
    mBoxText.setTextFillColor(sf::Color::Black);

    mTriangleLeft.setPointCount(3);
    mTriangleLeft.setInitAngle(3.141592654f); // pi
    mTriangleLeft.setFillColor(Constants::BackGroundTextColor);

    mTriangleRight.setPointCount(3);
    mTriangleRight.setInitAngle(0);
    mTriangleRight.setFillColor(Constants::BackGroundTextColor);

    // Init
    mPositionType = 0;
    mBoxText.setText(Constants::PositionText[0]);

    updateShape();
}

void SelectPositionBlock::setSize(sf::Vector2f size) { setSize(size.x, size.y); }
void SelectPositionBlock::setSize(float x, float y) {
    mWidth  = x;
    mHeight = y;
    updateShape();
}

void SelectPositionBlock::setPosition(sf::Vector2f position) {
    mPosition = position;
    updateShape();
}
void SelectPositionBlock::setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }

void SelectPositionBlock::setSelectPositionList(Vector<int> &list) {
    mSelectPositionList = list;
    mPositionType       = 0;
    mBoxText.setText(Constants::PositionText[getPositionType()]);
}

void SelectPositionBlock::updateType(int add) {
    add += mSelectPositionList.size();
    (mPositionType += add) %= mSelectPositionList.size();
    mBoxText.setText(Constants::PositionText[getPositionType()]);
}

int SelectPositionBlock::getPositionType() const {
    return mSelectPositionList[mPositionType];
}

void SelectPositionBlock::draw(sf::RenderTarget& target) {
    mBoxText.draw(target);
    target.draw(mTriangleLeft);
    target.draw(mTriangleRight);
}

void SelectPositionBlock::updateShape() {
    if (mWidth < 1 || mHeight < 1) {
        mWidth = mHeight = 1;
    }
    // 530 x 60
    float scaleX = mWidth / 530;
    mBoxText.setSize(sf::Vector2f(390 * scaleX, mHeight));
    mTriangleLeft.setRadius(mHeight / 2);
    mTriangleRight.setRadius(mHeight / 2);

    mBoxText.setPosition(mPosition + sf::Vector2f(70 * scaleX, 0));
    mTriangleLeft.setPosition(mPosition + sf::Vector2f(mHeight / 2, mHeight / 2));
    mTriangleRight.setPosition(mPosition + sf::Vector2f(mWidth - mHeight / 2, mHeight / 2));
}