#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

enum movement_states
{
    IDLE = 0,
    MOVING,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN
};

class MovementComponent
{
private:
    sf::Sprite&     sprite;
    sf::Vector2f    velocity;

    float           acceleration;
    float           deceleration;
    float           maxVelocity;
                                            // Privat functions
public:
    MovementComponent(sf::Sprite & sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

                                            // Accessors
    const sf::Vector2f& getVelocity() const;
    const float&        getVelocityMax() const;

                                            // Functions
    const bool          getStates(const short unsigned state) const;

    void                move(const float dir_x, const float dir_y, const float & dt);
    void                update(float const & dt);
};

