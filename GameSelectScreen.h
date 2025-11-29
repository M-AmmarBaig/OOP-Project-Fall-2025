#pragma once
#include "BaseScreen.h"
#include "Button.h"

class GameSelectScreen : public BaseScreen {
private:
    sf::Text titleText;
    
    Button* memoryMatchButton;
    Button* mathSpeedButton;
    Button* reactionTimeButton;
    Button* backButton;

public:
    GameSelectScreen(Engine* app);
    ~GameSelectScreen();

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
