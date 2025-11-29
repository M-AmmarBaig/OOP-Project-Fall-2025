#include "AnalyticsMenuScreen.h"
#include "Engine.h"
#include "MainMenuScreen.h"
#include "GameAnalyticsScreen.h"
#include "OverallAnalyticsScreen.h"
#include <iostream>

AnalyticsMenuScreen::AnalyticsMenuScreen(Engine* app)
    : BaseScreen(app),
      titleText(*app->getFont())
{
    sf::Vector2u windowSize = app->getWindow().getSize();
    float centerX = windowSize.x / 2.0f;
    
    titleText.setString("ANALYTICS");
    titleText.setCharacterSize(35);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(2.0f);
    titleText.setStyle(sf::Text::Bold);
    
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin({titleBounds.size.x / 2.0f, titleBounds.size.y / 2.0f});
    titleText.setPosition({centerX, 60.f});
    
    float btnWidth = 280.f;
    float btnHeight = 60.f;
    float btnX = centerX - (btnWidth / 2.0f);
    float startY = 150.f;
    float gap = 80.f;
    
    memoryMatchButton = new Button(
        btnX, startY, btnWidth, btnHeight,
        app->getFont(),
        "Memory Match Stats",
        sf::Color(70, 70, 70),
        sf::Color(100, 100, 100),
        sf::Color(150, 100, 200)
    );
    
    mathSpeedButton = new Button(
        btnX, startY + gap, btnWidth, btnHeight,
        app->getFont(),
        "Math Speed Stats",
        sf::Color(70, 70, 70),
        sf::Color(100, 100, 100),
        sf::Color(200, 150, 50)
    );
    
    reactionTimeButton = new Button(
        btnX, startY + (gap * 2), btnWidth, btnHeight,
        app->getFont(),
        "Reaction Time Stats",
        sf::Color(70, 70, 70),
        sf::Color(100, 100, 100),
        sf::Color(50, 200, 100)
    );
    
    stroopTestButton = new Button(
        btnX, startY + (gap * 3), btnWidth, btnHeight,
        app->getFont(),
        "Stroop Test Stats",
        sf::Color(70, 70, 70),
        sf::Color(100, 100, 100),
        sf::Color(200, 100, 200)
    );
    
    overallButton = new Button(
        btnX, startY + (gap * 4), btnWidth, btnHeight,
        app->getFont(),
        "Overall Performance",
        sf::Color(70, 70, 70),
        sf::Color(100, 100, 100),
        sf::Color(255, 200, 50)
    );
    
    float backBtnWidth = 150.f;
    float backBtnHeight = 50.f;
    backButton = new Button(
        centerX - (backBtnWidth / 2.0f), startY + (gap * 5.2f),
        backBtnWidth, backBtnHeight,
        app->getFont(),
        "Back",
        sf::Color(70, 70, 70),
        sf::Color(100, 100, 100),
        sf::Color(200, 50, 50)
    );
}

AnalyticsMenuScreen::~AnalyticsMenuScreen() {
    delete memoryMatchButton;
    delete mathSpeedButton;
    delete reactionTimeButton;
    delete stroopTestButton;
    delete overallButton;
    delete backButton;
}

void AnalyticsMenuScreen::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            
            if (memoryMatchButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new GameAnalyticsScreen(engine, 0));
            }
            else if (mathSpeedButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new GameAnalyticsScreen(engine, 1));
            }
            else if (reactionTimeButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new GameAnalyticsScreen(engine, 2));
            }
            else if (stroopTestButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new GameAnalyticsScreen(engine, 3));
            }
            else if (overallButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new OverallAnalyticsScreen(engine));
            }
            else if (backButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new MainMenuScreen(engine));
            }
        }
    }
}

void AnalyticsMenuScreen::update(sf::Time deltaTime) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(engine->getWindow());
    memoryMatchButton->update(mousePos);
    mathSpeedButton->update(mousePos);
    reactionTimeButton->update(mousePos);
    stroopTestButton->update(mousePos);
    overallButton->update(mousePos);
    backButton->update(mousePos);
}

void AnalyticsMenuScreen::render(sf::RenderWindow& window) {
    window.draw(titleText);
    memoryMatchButton->render(window);
    mathSpeedButton->render(window);
    reactionTimeButton->render(window);
    stroopTestButton->render(window);
    overallButton->render(window);
    backButton ->render(window);
}
