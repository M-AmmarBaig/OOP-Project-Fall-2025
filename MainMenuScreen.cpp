#include "MainMenuScreen.h"
#include "Engine.h"
#include <iostream>

MainMenuScreen::MainMenuScreen(Engine* app)
    : BaseScreen(app),
      titleText(*app->getFont())
{
    //getting my own windows screen dimensions to figure out the layout for a vertical screen.
    sf::Vector2u windowSize = app->getWindow().getSize();
    float centerX = windowSize.x / 2.0f;

    titleText.setString("BRAIN GAMES");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(textRect.size.x / 2.0f, textRect.size.y / 2.0f));
    titleText.setPosition(sf::Vector2f(centerX, 150.f)); // 150px from top

    float btnWidth = 300.f;
    float btnHeight = 70.f;
    float btnX = centerX - (btnWidth / 2.0f);

    float startY = 400.f;
    float gap = 100.f;

    playButton = new Button(btnX, startY, btnWidth, btnHeight, app->getFont(), "Play Game",
                            sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(50, 200, 50));

    analyticsButton = new Button(btnX, startY + gap, btnWidth, btnHeight, app->getFont(), "Analytics",
                                 sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(50, 50, 200));

    exitButton = new Button(btnX, startY + (gap * 2), btnWidth, btnHeight, app->getFont(), "Exit",
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
