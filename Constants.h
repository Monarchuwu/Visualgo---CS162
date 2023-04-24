#pragma once
#include <SFML/Graphics.hpp>

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
    const sf::Vector2f ShiftNode = sf::Vector2f(160.f, 0.f); // transform between 2 node

    /// Control Table Constants
    // Control Table
    extern sf::Color ControlTableThemeColor;
    // Button Main
    extern sf::Color ButtonMainColor;
    constexpr size_t ButtonMainCharacterSize = 35;
    // Parameter Table
    extern sf::Color ParameterTableThemeColor;

    // Misc
    constexpr int MinVal = 0;
    constexpr int MaxVal = 99;

    void init();
} // namespace Constants