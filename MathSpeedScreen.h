#pragma once
#include "BaseScreen.h"
#include "MathSpeedGame.h"
#include "Button.h"
#include <string>

class MathSpeedScreen : public BaseScreen {
private:
    MathSpeedGame* game;
    
    sf::Text titleText;
    sf::Text timerText;
    sf::Text scoreText;
    sf::Text equationText;
    sf::Text inputPromptText;
    sf::Text inputText;
    sf::Text feedbackText;
    
    std::string userInput;
    bool showFeedback;
    float feedbackTimer;
    
    Button* backButton;

public:
    MathSpeedScreen(Engine* app);
    ~MathSpeedScreen();

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
