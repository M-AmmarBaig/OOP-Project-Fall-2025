#pragma once
#include "BaseScreen.h"
#include "MemoryMatch.h"
#include "Button.h"
#include <vector>

class MemoryMatchScreen : public BaseScreen {
private:
    MemoryMatch* game;
    
    sf::Text titleText;
    sf::Text scoreText;
    sf::Text instructionText;
    sf::Text sequenceDisplayText;
    sf::Text inputPromptText;
    sf::Text inputText;
    sf::Text feedbackText;
    
    std::string userInput;
    bool isShowingSequence;
    int sequenceIndex;
    float sequenceTimer;
    int userSequenceIndex;
    
    bool showFeedback;
    float feedbackTimer;
    
    Button* backButton;

public:
    MemoryMatchScreen(Engine* app);
    ~MemoryMatchScreen();

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
