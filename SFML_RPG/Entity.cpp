#include "Entity.h"

void Entity::initVariable()
{
    movementComponent   = NULL;
    animationComponent  = NULL;
    hitboxComponent     = NULL;
}

Entity::Entity()
{
    initVariable();
}

Entity::~Entity()
{
    delete movementComponent;
    delete animationComponent;
    delete hitboxComponent;
}

void Entity::setTexture(sf::Texture & texture)
{
    sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
    animationComponent = new AnimationComponent(sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
    hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::setPosition(const float x, const float y)
{
    sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float & dt)
{
    if (movementComponent)
    {
        movementComponent->move(dir_x, dir_y, dt);                  // Set move Velocity
    }
}

void Entity::update(const float& dt)
{
    
}

void Entity::render(sf::RenderTarget& target)
{
    target.draw(sprite);

    if (hitboxComponent)
        hitboxComponent->render(target);
}
