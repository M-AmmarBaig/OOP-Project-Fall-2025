#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class SoundManager; 
class Button {
private:
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    SoundManager* soundManager; 

public:
    Button(float x, float y, float width, float height,
           sf::Font* font, std::string text,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
           SoundManager* soundManager);

    ~Button();

    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderTarget& target);
    bool isClicked(const sf::Vector2i& mousePos, sf::Mouse::Button button);
};

#endif
