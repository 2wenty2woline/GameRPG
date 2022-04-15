#include "Button.h"

Button::Button(float _x, float _y, float width, float height,
               sf::Font* font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color)
{
    buttonStates        = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(_x, _y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idle_Color);
    
    this->font          = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2 );

    textIdleColor       = text_idle_color;
    textHoverColor      = text_hover_color;
    textActiveColor     = text_active_color;

    this->idleColor     = idle_Color;
    this->hoverColor    = hover_Color;
    this->activeColor   = active_Color;
}

Button::~Button()
{

}

                                                                    // Accessors
const bool Button::isPressed() const
{
    if (buttonStates == BTN_ACTIVE)
    {
        return true;
    }
    return false;
}

                                                                    // Functions
void Button::update(const sf::Vector2f mousePos)
{
                                                                    // update the booleans for hover and pressed
    
                                                                    // IDLE
    buttonStates = BTN_IDLE;

                                                                    // HOVER
    if (shape.getGlobalBounds().contains(mousePos))
    {
        buttonStates = BTN_HOVER;

                                                                    // PRESSED
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            buttonStates = BTN_ACTIVE;
        }
    }

    switch (buttonStates)
    {
    case BTN_IDLE:
        shape.setFillColor(idleColor);
        text.setFillColor(textIdleColor);
        break;
    case BTN_HOVER:
        shape.setFillColor(hoverColor);
        text.setFillColor(textHoverColor);
        break;
    case BTN_ACTIVE:
        shape.setFillColor(activeColor);
        text.setFillColor(textActiveColor);
        break;
    default:
        shape.setFillColor(sf::Color::Red);
        text.setFillColor(sf::Color::Blue);
        break;
    }
}

void Button::render(sf::RenderTarget& target)
{
    target.draw(shape);
    target.draw(text);
}
