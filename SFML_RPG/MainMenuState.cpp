#include "MainMenuState.h"

void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
    background.setSize(
        sf::Vector2f
        (
            static_cast<float>(window->getSize().x),
            static_cast<float>(window->getSize().y)
        )
    );

    if (!backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
    {
        throw "ERROR::MAINMENUSTATE::COULD NOT LOAD BACKGROUND!";
    }
    
    background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts()
{
    if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!";
    }
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
    buttons["GAME_STATE"] = new Button(150, 300, 150, 50,
        &font, "New Game", 50,
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["SETTINGS"] = new Button(150, 400, 150, 50,
        &font, "Settings", 50,
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
    
    buttons["EDITOR_STATE"] = new Button(150, 500, 150, 50,
        &font, "Editor", 50,
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["EXIT_STATE"] = new Button(150, 600, 150, 50,
        &font, "Quit", 50,
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

                                                                    // Constructor & Destructor
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
    State(window, supportedKeys, states)
{
    initVariables();
    initBackground();
    initFonts();
    initKeybinds();
    initButtons();
}

MainMenuState::~MainMenuState()
{
    auto it = buttons.begin();

    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}

                                                                    // Functions
void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButton()
{
                                                                    // Update all buttons in the state 
    for (auto  it : buttons)
    {
        it.second->update(mousePosView);
    }

                                                                    // New game
    if (buttons["GAME_STATE"]->isPressed())
    {
        states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

                                                                    // Editor state
    if (buttons["EDITOR_STATE"]->isPressed())
    {
        states->push(new EditorState(this->window, this->supportedKeys, this->states));
    }

                                                                    // Quit the game
    if (buttons["EXIT_STATE"]->isPressed())
    {
        endState();
    }
}

void MainMenuState::update(const float& dt)
{
    updateMousePositions();
    updateInput(dt);
    updateButton();
}

void MainMenuState::renderButton(sf::RenderTarget& target)
{
    for (auto it : buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = window;

    target->draw(background);
    
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
