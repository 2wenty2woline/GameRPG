#pragma once

#include "MainMenuState.h"

class Game
{
private:

                                        // Variable
    sf::RenderWindow*               window;
    sf::Event                       sfEvent;
    sf::Clock                       dtClock;
    sf::ContextSettings             windowSettings;

    std::stack<State*>              states;

    std::map<std::string, int>      supportedKeys;
    std::vector<sf::VideoMode>      videoModes;

    float                           dt;
    bool                            fullscreen;

                                        // Init
    void initVariables();
    void initWindow();
    void initKeys();
    void initStates();

public:
    Game();
    virtual ~Game();

                                        // Func

                                        // Regular
    void endApplication();
                                        // Update
    void updateSFMLEvents();
    void updateDt();
    void update();

                                        // Render
    void render();

                                        // Core
    void run();
};

