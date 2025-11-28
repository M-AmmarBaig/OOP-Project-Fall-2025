#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include <vector>

class MainMenuScreen : public BaseScreen {
private:
    sf::Text titleText;

    // --- NEW: Background Variables ---
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    // ---------------------------------

    Button* playButton;
    Button* analyticsButton;
    Button* exitButton;

public:
    MainMenuScreen(Engine* app);
    ~MainMenuScreen();

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
