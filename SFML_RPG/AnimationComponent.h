#pragma once
#include <iostream>
#include <sstream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class AnimationComponent
{
private:
    class Animation
    {
    public:
        sf::Sprite&     sprite;
        sf::Texture&    textureSheet;
        sf::IntRect     startRect;
        sf::IntRect     currentRect;
        sf::IntRect     endRect;

        int             width;
        int             height;
        float           animationTimer;
        float           timer;

    public:
        Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float speed,
                  int start_frame_x, int start_frame_y, int end_x, int end_y,
                  int width, int height);

                                            // Function Animation
        bool play(const float & dt);
        bool play(const float & dt, float percent);
        void reset();
    };

    sf::Sprite&                         sprite;
    sf::Texture&                        textureSheet;
    std::map<std::string, Animation*>   animations;

    Animation*                          lastAnimation;
    Animation*                          priorityAnimation;

public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture & texture_sheet);
    virtual ~AnimationComponent();
     
                                            // Function
    void addAnimation(const std::string key, float animation_timer,
                      int start_frame_x, int start_frame_y, int frames_x, int frames_y,
                      int width, int heigh);

    void play(const std::string key, const float & dt, const bool priority = false);
    void play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};
