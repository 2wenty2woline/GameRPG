#include "AnimationComponent.h"

                                                                // Animation Class
AnimationComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer,
                                         int start_frame_x, int start_frame_y, int frames_x, int frames_y,
                                         int width, int height) :
    sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), timer(0.f), width(width), height(height)
{
    startRect       = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
    currentRect     = startRect;
    endRect         = sf::IntRect(frames_x * width, frames_y * height, width, height);
    this->sprite.setTexture(texture_sheet);
    this->sprite.setTextureRect(startRect);
}

bool AnimationComponent::Animation::play(const float& dt)
{
                                                            // Update timer
    bool done = false;

    timer += 100.f * dt;
    if (timer >= animationTimer)
    {
        // Reset timer
        timer = 0.f;

        // Animate
        if (currentRect != endRect)
        {
            currentRect.left += width;
        }
        // Reset Animate
        else
        {
            currentRect.left = startRect.left;
            done = true;
        }
        this->sprite.setTextureRect(currentRect);
    }
    return done;
}

bool AnimationComponent::Animation::play(const float& dt, float percent)
{
    if (percent < 0.5f)
        percent = 0.5f;

    bool done = false;
                                                            // Update timer
    timer += percent * 100.f * dt;
    if (timer >= animationTimer)
    {
        // Reset timer
        timer = 0.f;

        // Animate
        if (currentRect != endRect)
        {
            currentRect.left += width;
        }
        // Reset Animate
        else
        {
            currentRect.left = startRect.left;
            done = true;
        }
        this->sprite.setTextureRect(currentRect);
    }
    return done;
}

void AnimationComponent::Animation::reset()
{
    timer       = animationTimer;
    currentRect = startRect;
}

                                                                // Constructor & Destructor
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet) :
    sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
    for (auto& i : animations)
    {
        delete i.second;
    }
}

                                                                // Function
void AnimationComponent::addAnimation(const std::string key, float animation_timer,
                                      int start_frame_x, int start_frame_y, int frames_x, int frames_y,
                                      int width, int heigh)
{
    animations[key] = new Animation(this->sprite, this->textureSheet, animation_timer,
                                    start_frame_x, start_frame_y, frames_x, frames_y,
                                    width, heigh);
}

void AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
    if (priorityAnimation) // change !!!!!!!!!!!!!!!!!!!!!!
    {
        if (priorityAnimation == animations[key])
        {
            if (lastAnimation != animations[key])
            {
                if (!lastAnimation)// lastAnimation == NULL
                {
                    lastAnimation = animations[key];
                }
                else
                {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }

            if (animations[key]->play(dt))
            {
                priorityAnimation = NULL;
            }
        }
    }
    else
    {
        // CHANGE
        if (priority)
        {
            priorityAnimation = animations[key];
        }

        if (lastAnimation != animations[key])
        {
            if (!lastAnimation)// lastAnimation == NULL
            {
                lastAnimation = animations[key];
            }
            else
            {
                lastAnimation = animations[key];
                lastAnimation->reset();
            }
        }
        animations[key]->play(dt);
    }
}

void AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
    if (priorityAnimation) // change !!!!!!!!!!!!!!!!!!!!!!
    {
        if (priorityAnimation == animations[key])
        {
            if (lastAnimation != animations[key])
            {
                if (!lastAnimation) // lastAnimation == NULL
                {
                    lastAnimation = animations[key];
                }
                else
                {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }

            if (animations[key]->play(dt))
            {
                animations[key]->play(dt, abs(modifier / modifier_max));
            }
        }
    }
    else
    {
        // CHANGE
        if (priority)
        {
            priorityAnimation = animations[key];
        }

        if (lastAnimation != animations[key])
        {
            if (!lastAnimation) // lastAnimation == NULL
            {
                lastAnimation = animations[key];
            }
            else
            {
                lastAnimation = animations[key];
                lastAnimation->reset();
            }
        }
        animations[key]->play(dt, abs(modifier / modifier_max));
    }
}
