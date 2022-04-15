#pragma once
#include "State.h"
#include "Button.h"

class EditorState :
    public State
{

private:
    // Variables
    sf::Font                        font;

    std::map<std::string, Button*>  buttons;
    // Function
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds() override;
    void initButtons();

public:
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~EditorState();

    // Function
    void updateInput(const float& dt);
    void updateButton();
    void update(const float& dt);

    void renderButton(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);


};

