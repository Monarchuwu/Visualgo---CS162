#pragma once
#include "Button.h"
#include "CircleShape.h"
#include "Vector.h"

class SelectPositionBlock {
public:
    SelectPositionBlock(float width           = 0,
                        float height          = 0,
                        sf::Vector2f position = sf::Vector2f(0, 0));

    // Set size for Block
    void setSize(sf::Vector2f size);
    void setSize(float x, float y);

    // Set position for Block
    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);

    // Position Type
    void setSelectPositionList(Vector<int> &list);
    void updateType(int add);

    // Interact
    int getPositionType() const;
    virtual void draw(sf::RenderTarget &target);

private:
    void updateShape();

public:
    CircleShape mTriangleLeft;
    CircleShape mTriangleRight;

private:
    Button mBoxText;

    int mPositionType;
    Vector<int> mSelectPositionList;

    float mWidth;
    float mHeight;
    sf::Vector2f mPosition;
};

// Select Position Block : [325..855] x [530..590]
//
//// Select Position to Insert/Delete : [395..785] x [530..590]
//// Display: <Beginning (i = 0), Middle (i = 1..n-1), End (i = n)>
//Button mSelectPosition;
//// Triangle in the Left of mSelectPosition : [(355, 560), 30]
//CircleShape mTriangleLeft;
//// Triangle in the Right of mSelectPosition : [(825, 560), 30]
//CircleShape mTriangleRight;
