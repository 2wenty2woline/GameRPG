#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum bullon_states
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button
{
private:
    short unsigned      buttonStates;

    sf::RectangleShape  shape;
    sf::Font*           font;
    sf::Text            text;

    sf::Color           textIdleColor;
    sf::Color           textHoverColor;
    sf::Color           textActiveColor;

    sf::Color           idleColor;
    sf::Color           hoverColor;
    sf::Color           activeColor;

public:
    Button(float _x, float _y, float width, float height, 
           sf::Font* font, std::string text, unsigned character_size,
           sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
           sf::Color idle_Color, sf::Color hover_Color, sf::Color activ_Color);
    ~Button();

                                                    // Accessors
    const bool isPressed() const;

                                                    // Functions
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget& target);
};

