#include "Player.h"

void Player::initVariables()
{
    attack = false;
}

void Player::initComponents()
{

}

Player::Player(float x, float y, sf::Texture & texture_sheet)
{
    initVariables();

    setPosition(x, y);

    createHitboxComponent(sprite, 86.f, 65.f, 86.f, 115.f);
    createMovementComponent(350.f, 15.f, 5.f);
    createAnimationComponent(texture_sheet);

    animationComponent->addAnimation("IDLE",    11.f,  0,   0,  13,  0,  192,   192);
    animationComponent->addAnimation("WALK",    7.f,   0,   1,  11,  1,  192,   192);
    animationComponent->addAnimation("ATTACK",  6.f,   0,   2,  13,  2,  192*2, 192);
}

Player::~Player()
{
}

void Player::update(const float& dt)
{
    movementComponent->update(dt);
    
    // CHANGE
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //attack
    {
        attack = true;
    }
    if (attack)
    {
        animationComponent->play("ATTACK", dt, true);
    }
    // END CHENGE


    if (movementComponent->getStates(IDLE))
    {
        animationComponent->play("IDLE", dt);
    }
    else if (movementComponent->getStates(MOVING_LEFT))
    {
        sprite.setOrigin(0.f, 0.f);
        sprite.setScale(1.f, 1.f);
        animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getVelocityMax());
    }
    else if (movementComponent->getStates(MOVING_RIGHT))
    {
        sprite.setOrigin(258.f, 0.f);
        sprite.setScale(-1.f, 1.f);
        animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getVelocityMax());
    }
    else if (movementComponent->getStates(MOVING_UP))
    {
        animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getVelocityMax());
    }
    else if (movementComponent->getStates(MOVING_DOWN))
    {
        animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getVelocityMax());
    }

    hitboxComponent->update();
}
