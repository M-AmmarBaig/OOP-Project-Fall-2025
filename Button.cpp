#include "Button.h"
#include "SoundManager.h"

Button::Button(float x, float y, float width, float height,
               sf::Font* font, std::string textStr,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
               SoundManager* soundManager)
    : font(font), text(*font), soundManager(soundManager)
{
    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setPosition({x, y});
    this->shape.setSize({width, height});
    this->shape.setFillColor(this->idleColor);

    this->text.setString(textStr);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(20);

    sf::FloatRect textBounds = this->text.getGlobalBounds();
    sf::FloatRect shapeBounds = this->shape.getGlobalBounds();

    this->text.setPosition({
        this->shape.getPosition().x + (shapeBounds.size.x / 2.f) - (textBounds.size.x / 2.f),
        this->shape.getPosition().y + (shapeBounds.size.y / 2.f) - (textBounds.size.y / 2.f)
    });
}

Button::~Button() {
}

bool Button::isClicked(const sf::Vector2i& mousePos, sf::Mouse::Button button) {
    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        if (button == sf::Mouse::Button::Left) {
            if (soundManager) {
                soundManager->playButtonClick();
            }
            return true;
        }
    }
    return false;
}

void Button::update(const sf::Vector2i& mousePos) {
    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        this->shape.setFillColor(this->hoverColor);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            this->shape.setFillColor(this->activeColor);
        }
    } else {
        this->shape.setFillColor(this->idleColor);
    }
}

void Button::render(sf::RenderTarget& target) {
    target.draw(this->shape);
    target.draw(this->text);
}
