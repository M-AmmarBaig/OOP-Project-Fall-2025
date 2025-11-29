#pragma once
#include "BaseScreen.h"
#include "ReactionTimeGame.h"
#include "Button.h"

class ReactionTimeScreen : public BaseScreen {
private:
    ReactionTimeGame* game;
    
    sf::Text titleText;
    sf::Text timerText;
    sf::Text scoreText;
    sf::Text instructionText;
    sf::Text statsText;
    sf::Text reactionText;
    
    sf::CircleShape targetCircle;
    
    bool showReactionFeedback;
    float reactionFeedbackTimer;
    float lastReactionTime;
    
    Button* backButton;

public:
    ReactionTimeScreen(Engine* app);
    ~ReactionTimeScreen();

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
