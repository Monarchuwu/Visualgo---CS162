#pragma once
#include <SFML/Graphics.hpp>

namespace Constants {
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
    constexpr float CirleNodeRadius      = 26.f;
    constexpr float NodeOutlineThinkness = 4.f;
    extern sf::Color NodeFillColor;
    extern sf::Color NodeOutlineColor;
    extern sf::Color TextNodeColor;
    // Text
    constexpr size_t CharacterSize = 24;

    /// Basic List Constants
    // Max Count Node
    const size_t MaxCountNode = 10;
    // Shift Node by Arrow
    const sf::Vector2f ShiftNode = sf::Vector2f(160.f, 0.f); // transform between 2 node

    /// Arrow Constants
    constexpr float HeadArrowRadius = 7.f;

    // Misc
    constexpr int MinVal = 0;
    constexpr int MaxVal = 99;

    void init();
} // namespace Constants