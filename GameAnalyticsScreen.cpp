#include "GameAnalyticsScreen.h"
#include "Engine.h"
#include "AnalyticsMenuScreen.h"
#include <sstream>
#include <iomanip>

GameAnalyticsScreen::GameAnalyticsScreen(Engine* app, int gameIdx)
    : BaseScreen(app),
      gameIndex(gameIdx),
      stats(app->getStats()),
      titleText(*app->getFont()),
      gameNameText(*app->getFont()),
      highScoreText(*app->getFont()),
      avgScoreText(*app->getFont()),
      playCountText(*app->getFont()),
      recentLabelText(*app->getFont())
{
    for (int i = 0; i < 5; i++) {
        recentScoresText[i] = new sf::Text(*app->getFont());
        recentScoresText[i]->setCharacterSize(20);
        recentScoresText[i]->setFillColor(sf::Color::White);
    }
    
    sf::Vector2u windowSize = app->getWindow().getSize();
    float centerX = windowSize.x / 2.0f;
    
    titleText.setString("GAME STATISTICS");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(2.0f);
    titleText.setStyle(sf::Text::Bold);
    
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin({titleBounds.size.x / 2.0f, titleBounds.size.y / 2.0f});
    titleText.setPosition({centerX, 50.f});
    
    gameNameText.setString(stats->GetGameName(gameIndex));
    gameNameText.setCharacterSize(28);
    gameNameText.setFillColor(sf::Color::Yellow);
    gameNameText.setStyle(sf::Text::Bold);
    
    sf::FloatRect gameBounds = gameNameText.getLocalBounds();
    gameNameText.setOrigin({gameBounds.size.x / 2.0f, gameBounds.size.y / 2.0f});
    gameNameText.setPosition({centerX, 110.f});
    
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::Green);
    
    avgScoreText.setCharacterSize(24);
    avgScoreText.setFillColor(sf::Color::White);
    
    playCountText.setCharacterSize(24);
    playCountText.setFillColor(sf::Color::White);
    
    recentLabelText.setString("Recent Scores:");
    recentLabelText.setCharacterSize(22);
    recentLabelText.setFillColor(sf::Color(200, 200, 200));
    
    backButton = new Button(
        centerX - 75.f, windowSize.y - 70.f,
        150.f, 50.f,
        app->getFont(),
        "Back",
        sf::Color(70, 70, 70),
        sf::Color(100, 100, 100),
        sf::Color(200, 50, 50)
    );
}

GameAnalyticsScreen::~GameAnalyticsScreen() {
    for (int i = 0; i < 5; i++) {
        delete recentScoresText[i];
    }
    delete backButton;
}

void GameAnalyticsScreen::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            
            if (backButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new AnalyticsMenuScreen(engine));
            }
        }
    }
}

void GameAnalyticsScreen::update(sf::Time deltaTime) {
    float centerX = engine->getWindow().getSize().x / 2.0f;
    
    std::ostringstream highStream;
    highStream << "High Score: " << static_cast<int>(stats->GetBestScore(gameIndex));
    highScoreText.setString(highStream.str());
    sf::FloatRect highBounds = highScoreText.getLocalBounds();
    highScoreText.setOrigin({highBounds.size.x / 2.0f, highBounds.size.y / 2.0f});
    highScoreText.setPosition({centerX, 180.f});
    
    std::ostringstream avgStream;
    avgStream << "Average Score: " << std::fixed << std::setprecision(1) 
              << stats->GetAverageScore(gameIndex);
    avgScoreText.setString(avgStream.str());
    sf::FloatRect avgBounds = avgScoreText.getLocalBounds();
    avgScoreText.setOrigin({avgBounds.size.x / 2.0f, avgBounds.size.y / 2.0f});
    avgScoreText.setPosition({centerX, 220.f});
    
    std::ostringstream playStream;
    playStream << "Times Played: " << stats->GetGameSpecificPlayCount(gameIndex);
    playCountText.setString(playStream.str());
    sf::FloatRect playBounds = playCountText.getLocalBounds();
    playCountText.setOrigin({playBounds.size.x / 2.0f, playBounds.size.y / 2.0f});
    playCountText.setPosition({centerX, 260.f});
    
    sf::FloatRect labelBounds = recentLabelText.getLocalBounds();
    recentLabelText.setOrigin({labelBounds.size.x / 2.0f, labelBounds.size.y / 2.0f});
    recentLabelText.setPosition({centerX, 330.f});
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(engine->getWindow());
    backButton->update(mousePos);
}

void GameAnalyticsScreen::render(sf::RenderWindow& window) {
    float centerX = window.getSize().x / 2.0f;
    
    window.draw(titleText);
    window.draw(gameNameText);
    window.draw(highScoreText);
    window.draw(avgScoreText);
    window.draw(playCountText);
    window.draw(recentLabelText);
    
    backButton->render(window);
}
