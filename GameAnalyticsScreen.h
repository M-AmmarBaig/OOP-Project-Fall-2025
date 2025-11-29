#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include "StatisticsManager.h"

class GameAnalyticsScreen : public BaseScreen {
private:
    int gameIndex;
    StatisticsManager* stats;
    
    sf::Text titleText;
    sf::Text gameNameText;
    sf::Text highScoreText;
    sf::Text avgScoreText;
    sf::Text playCountText;
    sf::Text recentLabelText;
    sf::Text* recentScoresText[5];
    
    Button* backButton;

public:
    GameAnalyticsScreen(Engine* app, int gameIdx);
    ~GameAnalyticsScreen();

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
