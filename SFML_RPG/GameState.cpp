#include "GameState.h"

void GameState::initKeybinds()
{
    std::ifstream ifs("Config/gamestate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key     = "";
        std::string key2    = "";

        while (ifs >> key >> key2)
        {
            keybinds[key]   = supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void GameState::initTextures()
{
    if (!textures["PLAYER"].loadFromFile("Resources/Images/Sprites/Player/PLAYER.png"))
    {
        throw "ERROR::GAME_STATE::PLAYER::CLOUD_NOT_LOAD_PLAYER";
    }
}

void GameState::initPlayers()
{
    player = new Player(100, 100, this->textures["PLAYER"]);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
    State(window, supportedKeys, states)
{
    initKeybinds();
    initTextures();
    initPlayers();
}

GameState::~GameState()
{
    delete player;
}

                                                        // Function
void GameState::updateInput(const float& dt)
{
                                                        // Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
    {
        player->move(-1.f, 0.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
    {
        player->move(1.f, 0.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
    {
        player->move(0, -1.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
    {
        player->move(0.f, 1.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
    {
        endState();
    }
}

void GameState::update(const float& dt)
{
    updateMousePositions();
    updateInput(dt);

    player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = window;

    player->render(*target);
}
