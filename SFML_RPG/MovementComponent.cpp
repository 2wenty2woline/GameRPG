#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
    return velocity;
}

const float& MovementComponent::getVelocityMax() const
{
    return maxVelocity;
}

const bool MovementComponent::getStates(const short unsigned state) const
{
    switch (state)
    {
    case IDLE:
        if (velocity.x == 0.f && velocity.y == 0.f)
            return true;
        break;
    case MOVING:
        if (velocity.x != 0.f || velocity.y != 0.f)
            return true;
        break;
    case MOVING_LEFT:
        if (velocity.x < 0.f)
            return true;
        break;
    case MOVING_RIGHT:
        if (velocity.x > 0.f)
            return true;
        break;
    case MOVING_UP:
        if (velocity.y < 0.f)
            return true;
        break;
    case MOVING_DOWN:
        if (velocity.y > 0.f)
            return true;
        break;
    }

    return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float & dt)
{
    velocity.x += acceleration * dir_x;
    velocity.y += acceleration * dir_y;
}

void MovementComponent::update(float const& dt)
{
                                    // Check for positive X
    if (velocity.x > 0.f)
    {
        // MAX check positive
        if (velocity.x > maxVelocity)
            velocity.x = maxVelocity;
        
        // Deceleration X
        velocity.x -= deceleration;
        if (velocity.x < 0.f)
            velocity.x = 0.f;
    }
                                    // Check for negative X
    else if (velocity.x < 0.f)
    {
        // MAX check negative
        if (velocity.x < -maxVelocity)
            velocity.x = -maxVelocity;

        // Deceleration X
        velocity.x += deceleration;
        if (velocity.x > 0.f)
            velocity.x = 0.f;
    }                                    
                                    // Check for positive Y
    if (velocity.y > 0.f)
    {
        // MAX check positive
        if (velocity.y > maxVelocity)
            velocity.y = maxVelocity;

        // Deceleration Y
        velocity.y -= deceleration;
        if (velocity.y < 0.f)
            velocity.y = 0.f;
    }
                                    // Check for negative Y
    else if (velocity.y < 0.f)
    {
        // MAX check negative
        if (velocity.y < -maxVelocity)
            velocity.y = -maxVelocity;

        // Deceleration Y
        velocity.y += deceleration;
        if (velocity.y > 0.f)
            velocity.y = 0.f;
    }
                                    // Final move use move velocity
    sprite.move(velocity * dt);
}
