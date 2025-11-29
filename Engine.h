#pragma once
#include <SFML/Graphics.hpp>
#include "StatisticsManager.h"
#include "SoundManager.h"
#include "BaseScreen.h"

class Engine {
private:
    sf::RenderWindow window;
    BaseScreen* currentScreen;

    StatisticsManager statsManager;
    SoundManager soundManager;

    sf::Font mainFont;

public:
    Engine();
    ~Engine();

    void run();

    void switchScreen(BaseScreen* newScreen);

    StatisticsManager* getStats() { return &statsManager; }
    SoundManager* getSoundManager() { return &soundManager; }
    sf::Font* getFont() { return &mainFont; }
    sf::RenderWindow& getWindow() { return window; }
};
