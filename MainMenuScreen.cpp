#include "MainMenuScreen.h"
#include "Engine.h"
#include <iostream>

// FIX: Added titleText(*app->getFont()) to the initializer list
MainMenuScreen::MainMenuScreen(Engine* app) 
    : BaseScreen(app), 
      titleText(*app->getFont()) 
{
    // 1. Setup Title
    // (We don't need setFont here anymore because we did it above ^)
    titleText.setString("BRAIN GAMES");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setStyle(sf::Text::Bold);
    
    // Center the title roughly
    titleText.setPosition(sf::Vector2f(230.f, 50.f));

    // 2. Create Buttons
    // x, y, width, height, font, text, idleColor, hoverColor, activeColor
    playButton = new Button(250.f, 200.f, 300.f, 60.f, app->getFont(), "Play Game",
                            sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(50, 200, 50));

    analyticsButton = new Button(250.f, 300.f, 300.f, 60.f, app->getFont(), "Analytics",
                                 sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(50, 50, 200));

    exitButton = new Button(250.f, 400.f, 300.f, 60.f, app->getFont(), "Exit",
                            sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(200, 50, 50));
}

MainMenuScreen::~MainMenuScreen() {
    delete playButton;
    delete analyticsButton;
    delete exitButton;
}

void MainMenuScreen::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (playButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                std::cout << "Switching to Game Select..." << std::endl;
                // engine->switchScreen(new GameSelectScreen(engine));
            }
            
            if (analyticsButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                std::cout << "Switching to Analytics..." << std::endl;
                // engine->switchScreen(new AnalyticsScreen(engine));
            }

            if (exitButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                window.close();
            }
        }
    }
}

void MainMenuScreen::update(sf::Time deltaTime) {
    // We need to update buttons so they handle hover effects
    sf::Vector2i mousePos = sf::Mouse::getPosition(engine->getWindow());
    
    playButton->update(mousePos);
    analyticsButton->update(mousePos);
    exitButton->update(mousePos);
}

void MainMenuScreen::render(sf::RenderWindow& window) {
    window.draw(titleText);
    playButton->render(window);
    analyticsButton->render(window);
    exitButton->render(window);
}