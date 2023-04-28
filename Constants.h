#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

namespace Constants {
    /// Color Constants
    extern sf::Color StandardColor[4];

    /// Scene Constants
    // Scene Main [0..1600] x [0..900]
    constexpr int SceneWidth      = 1600;
    constexpr int SceneHeight     = 900;
    constexpr int FramesPerSecond = 20;
    const sf::Time TimePerFrame   = sf::seconds(1.f / FramesPerSecond);
    // Scene Visualize [0..1600] x [0..400]
    // Scene Visualize List [50..1550] x [100..350]
    const sf::Vector2f MidPointSceneVisual(800, 130);

    // Font Constants
    extern sf::Font Font;
    char const FontName[] = "arial.ttf";

    /// Node Constants
    // Body
    constexpr float CirleNodeRadius      = 25.f;
    constexpr float NodeOutlineThinkness = 5.f;
    extern sf::Color NodeFillColor;
    extern sf::Color NodeOutlineColor;
    extern sf::Color TextNodeColor;
    // Text
    constexpr size_t TextNodeCharacterSize = 26;

    /// Basic List Constants
    // Max Count Node
    const size_t MaxCountNode = 10;
    extern size_t CountNode;
    // Shift Node by Arrow
    const sf::Vector2f ShiftNode = sf::Vector2f(160.f, 0.f); // transform between 2 node

    /// Control Table Constants
    // Control Table
    extern sf::Color ControlTableThemeColor;
    // Button Main
    extern sf::Color ButtonMainColor;
    extern sf::Color ButtonMainColorClicked;
    constexpr size_t ButtonMainCharacterSize = 30;
    enum Operation { Init,
                     Insert,
                     Delete,
                     Update,
                     Allocate,
                     Access,
                     Search,
                     Push,
                     Pop,
                     Add,
                     Remove,
                     Clear
    };
    const std::string OperationText[12] = {
        "Init",
        "Insert",
        "Delete",
        "Update",
        "Allocate",
        "Access",
        "Search",
        "Push",
        "Pop",
        "Add",
        "Remove",
        "Clear"
    };
    // Parameter Table
    extern sf::Color ParameterTableThemeColor;
    extern sf::Color BackGroundTextColor;
    extern sf::Color BackGroundTextColorHold;
    // Position Row (Row 1)
    enum Position {
        Beginning,
        Middle,
        End
    };
    const std::string PositionText[3] = {
        "Beginning (i = 0)",
        "Middle (i = 1..n - 1)",
        "End (i = n)"
    };

    // Misc
    constexpr int MinVal = 0;
    constexpr int MaxVal = 99;

    void init();

} // namespace Constants