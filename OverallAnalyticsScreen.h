#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include "StatisticsManager.h"

class OverallAnalyticsScreen : public BaseScreen {
private:
    StatisticsManager* stats;
    
    sf::Text titleText;
    sf::Text brainScoreLabel;
    sf::Text brainScoreValue;
    sf::Text totalGamesText;
    sf::Text* gameSummaryTexts[4];
    
    Button* backButton;
    
    int calculateBrainScore();

public:
    OverallAnalyticsScreen(Engine* app);
    ~OverallAnalyticsScreen();

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
