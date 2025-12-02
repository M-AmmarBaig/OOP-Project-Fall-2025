#pragma once
#include "BaseScreen.h"
#include "StroopTestGame.h"
#include "Button.h"

class StroopTestScreen : public BaseScreen {
private:
    StroopTestGame* game;
    
    sf::Text titleText;
    sf::Text timerText;
    sf::Text scoreText;
    sf::Text instructionText;
    sf::Text wordText;
    sf::Text statsText;
    sf::Text feedbackText;
    
    Button* redButton;
    Button* blueButton;
    Button* greenButton;
    Button* yellowButton;
    Button* backButton;
    
    bool showFeedback;
    float feedbackTimer;

public:
    StroopTestScreen(Engine* app);
    ~StroopTestScreen();

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
    
    void handleColorButtonClick(StroopTestGame::ColorType color);
};
