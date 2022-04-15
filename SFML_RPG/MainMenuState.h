#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
                                                                // Variables
    sf::RectangleShape              background;
    sf::Texture                     backgroundTexture;
    sf::Font                        font;

    std::map<std::string, Button*>  buttons;
                                                                // Function
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds() override;
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

                                                                // Function
    void updateInput(const float& dt);
    void updateButton();
    void update(const float& dt);

    void renderButton(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);

};

