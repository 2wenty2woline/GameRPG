#include "EditorState.h"

void EditorState::initVariables()
{

}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
    if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw "ERROR::EDITORSTATE::COULD NOT LOAD FONT!";
    }
}

void EditorState::initKeybinds()
{
    std::ifstream ifs("Config/editorstate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            keybinds[key] = supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void EditorState::initButtons()
{

}

// Constructor & Destructor
EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
    State(window, supportedKeys, states)
{
    initVariables();
    initBackground();
    initFonts();
    initKeybinds();
    initButtons();
}

EditorState::~EditorState()
{
    auto it = buttons.begin();

    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Functions
void EditorState::updateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
    {
        endState();
    }
}

void EditorState::updateButton()
{
    // Update all buttons in the state 
    for (auto it : buttons)
    {
        it.second->update(mousePosView);
    }
}

void EditorState::update(const float& dt)
{
    updateMousePositions();
    updateInput(dt);
    updateButton();
}

void EditorState::renderButton(sf::RenderTarget& target)
{
    for (auto it : buttons)
    {
        it.second->render(target);
    }
}

void EditorState::render(sf::RenderTarget* target)
{
    if (!target)
        target = window;

    renderButton(*target);

    // REMOVE LATER!!!
    sf::Text mouseText;
    mouseText.setPosition(mousePosView.x, mousePosView.y - 50);
    mouseText.setFont(font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << mousePosView.x << " " << mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
    // REMOVE LATER!!!
}
