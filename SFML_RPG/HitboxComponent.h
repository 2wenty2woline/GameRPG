#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class HitboxComponent
{
private:
    sf::RectangleShape  hitbox;
    sf::Sprite&         sprite;
    float               offsetY;
    float               offsetX;

public:
    HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    virtual ~HitboxComponent();

                                        // Functions
    bool checkIntersect(const sf::FloatRect& frect);

    void update();
    void render(sf::RenderTarget& target);
};
