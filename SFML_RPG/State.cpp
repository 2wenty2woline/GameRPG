#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
    this->window        = window;
    this->states        = states;
    this->supportedKeys = supportedKeys;
    this->quit          = false;
}

State::~State()
{

}

const bool& State::getQuit() const
{
    return quit;
}

void State::updateMousePositions()
{
    mousePosScreen  = sf::Mouse::getPosition();
    mousePosWindow  = sf::Mouse::getPosition(*window);
    mousePosView    = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::endState()
{
    quit = true;
}
