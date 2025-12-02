#pragma once
#include "BaseScreen.h"
#include "Button.h"

class AnalyticsMenuScreen : public BaseScreen {
private:
    sf::Text titleText;
    
    Button* memoryMatchButton;
    Button* mathSpeedButton;
    Button* reactionTimeButton;
    Button* stroopTestButton;
    Button* overallButton;
    Button* backButton;

public:
    AnalyticsMenuScreen(Engine* app);
    ~AnalyticsMenuScreen();

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
