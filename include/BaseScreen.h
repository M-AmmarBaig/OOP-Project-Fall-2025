#pragma once
#include <SFML/Graphics.hpp>

class Engine;

class BaseScreen {
protected:
    Engine* engine;

public:
    BaseScreen(Engine* app) : engine(app) {}
    virtual ~BaseScreen() {}

    virtual void handleInput(const sf::Event& event, sf::RenderWindow& window) = 0;

    virtual void update(sf::Time deltaTime) = 0;

    virtual void render(sf::RenderWindow& window) = 0;
};
