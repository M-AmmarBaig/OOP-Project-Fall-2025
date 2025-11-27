#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Button Test");

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }


    Button testBtn(100.f, 100.f, 200.f, 50.f,
                   &font, "Play Game",
                   sf::Color(70, 70, 70),
                   sf::Color(150, 150, 150),                      sf::Color(20, 20, 150));
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        testBtn.update(sf::Mouse::getPosition(window));

        if (testBtn.isClicked(sf::Mouse::getPosition(window), sf::Mouse::Button::Left)) {
            std::cout << "Button was clicked!" << std::endl;
        }

        window.clear(sf::Color::White);
        testBtn.render(window);
        window.display();                   }

    return 0;
}
