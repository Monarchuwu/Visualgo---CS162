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
    // Shift Node by Arrow
    const sf::Vector2f ShiftNode = sf::Vector2f(130.f, 0.f); // transform between 2 node

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
        Beginning_0,
        Middle_0_n1,
        Middle_0_n,
        Middle_1_n1,
        Middle_1_n2,
        End_n1,
        End_n
    };
    const std::string PositionText[7] = {
        "Beginning (i = 0)",
        "Middle (i = 0..n - 1)",
        "Middle (i = 0..n)",
        "Middle (i = 1..n - 1)",
        "Middle (i = 1..n - 2)",
        "End (i = n - 1)",
        "End (i = n)"
    };
    const int SelectPosList[12] = {
        (1 << Middle_0_n1),                                      // Init
        (1 << Beginning_0) | (1 << Middle_1_n1) | (1 << End_n),  // Insert
        (1 << Beginning_0) | (1 << Middle_1_n2) | (1 << End_n1), // Delete
        (1 << Middle_0_n1),                                      // Update
        0,                                                       // Allocate (mark)
        0,                                                       // Access (mark)
        (1 << Middle_0_n),                                       // Search
        (1 << Beginning_0),                                      // Push
        (1 << End_n1),                                           // Pop
        0,                                                       // Add (mark)
        0,                                                       // Remove (mark)
        0,                                                       // Clear (mark)
    };

    // Misc
    constexpr int MinVal        = 0;
    constexpr int MaxVal        = 99;
    constexpr float pi          = 3.14159265359;
    const sf::Color OrangeColor = sf::Color(255, 165, 0);

    void init();

} // namespace Constants