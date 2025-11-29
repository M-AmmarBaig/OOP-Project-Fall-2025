#include "OverallAnalyticsScreen.h"
#include "Engine.h"
#include "AnalyticsMenuScreen.h"
#include <sstream>
#include <iomanip>

OverallAnalyticsScreen::OverallAnalyticsScreen(Engine* app)
    : BaseScreen(app),
      stats(app->getStats()),
      titleText(*app->getFont()),
      brainScoreLabel(*app->getFont()),
      brainScoreValue(*app->getFont()),
      totalGamesText(*app->getFont())
{
    for (int i = 0; i < 4; i++) {
        gameSummaryTexts[i] = new sf::Text(*app->getFont());
    }
    
    sf::Vector2u windowSize = app->getWindow().getSize();
    float centerX = windowSize.x / 2.0f;
    
    titleText.setString("OVERALL PERFORMANCE");
    titleText.setCharacterSize(28);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(2.0f);
    titleText.setStyle(sf::Text::Bold);
    
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin({titleBounds.size.x / 2.0f, titleBounds.size.y / 2.0f});
    titleText.setPosition({centerX, 50.f});
    
    brainScoreLabel.setString("BRAIN SCORE");
    brainScoreLabel.setCharacterSize(24);
    brainScoreLabel.setFillColor(sf::Color::Yellow);
    brainScoreLabel.setStyle(sf::Text::Bold);
    
    sf::FloatRect labelBounds = brainScoreLabel.getLocalBounds();
    brainScoreLabel.setOrigin({labelBounds.size.x / 2.0f, labelBounds.size.y / 2.0f});
    brainScoreLabel.setPosition({centerX, 110.f});
    
    brainScoreValue.setCharacterSize(48);
    brainScoreValue.setFillColor(sf::Color::Green);
    brainScoreValue.setStyle(sf::Text::Bold);
    
    totalGamesText.setCharacterSize(20);
    totalGamesText.setFillColor(sf::Color::White);
    
    for (int i = 0; i < 4; i++) {
        gameSummaryTexts[i]->setCharacterSize(18);
        gameSummaryTexts[i]->setFillColor(sf::Color(200, 200, 200));
    }
    
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

OverallAnalyticsScreen::~OverallAnalyticsScreen() {
    for (int i = 0; i < 4; i++) {
        delete gameSummaryTexts[i];
    }
    delete backButton;
}

int OverallAnalyticsScreen::calculateBrainScore() {
    int totalScore = 0;
    int gamesWithData = 0;
   // only working for memory match game on the other games it is not showing anything 
    for (int i = 0; i < 4; i++) {
        int playCount = stats->GetGameSpecificPlayCount(i);
        if (playCount > 0) {
            double avgScore = stats->GetAverageScore(i);
            double highScore = stats->GetBestScore(i);
            
            int gameScore = static_cast<int>((avgScore * 0.6) + (highScore * 0.4));
            totalScore += gameScore;
            gamesWithData++;
        }
    }
    
    if (gamesWithData == 0) return 0;
    
    return totalScore / gamesWithData;
}

void OverallAnalyticsScreen::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            
            if (backButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new AnalyticsMenuScreen(engine));
            }
        }
    }
}

void OverallAnalyticsScreen::update(sf::Time deltaTime) {
    float centerX = engine->getWindow().getSize().x / 2.0f;
    
    int brainScore = calculateBrainScore();
    std::ostringstream scoreStream;
    scoreStream << brainScore;
    brainScoreValue.setString(scoreStream.str());
    
    sf::FloatRect scoreBounds = brainScoreValue.getLocalBounds();
    brainScoreValue.setOrigin({scoreBounds.size.x / 2.0f, scoreBounds.size.y / 2.0f});
    brainScoreValue.setPosition({centerX, 155.f});
    //not getting any value for some games at all.
    std::ostringstream totalStream;
    totalStream << "Total Games Played: " << stats->GetGamesPlayedCount();
    totalGamesText.setString(totalStream.str());
    
    sf::FloatRect totalBounds = totalGamesText.getLocalBounds();
    totalGamesText.setOrigin({totalBounds.size.x / 2.0f, totalBounds.size.y / 2.0f});
    totalGamesText.setPosition({centerX, 220.f});
    
    const char* gameNames[] = {"Memory Match", "Math Speed", "Reaction Time", "Stroop Test"};
    float startY = 280.f;
    
    for (int i = 0; i < 4; i++) {
        std::ostringstream summaryStream;
        summaryStream << gameNames[i] << ": ";
        
        int playCount = stats->GetGameSpecificPlayCount(i);
        if (playCount > 0) {
            summaryStream << "Best=" << static_cast<int>(stats->GetBestScore(i))
                         << " | Avg=" << std::fixed << std::setprecision(1) 
                         << stats->GetAverageScore(i)
                         << " | Played=" << playCount;
        } else {
            summaryStream << "Not played yet";
        }
        
        gameSummaryTexts[i]->setString(summaryStream.str());
        
        sf::FloatRect gameBounds = gameSummaryTexts[i]->getLocalBounds();
        gameSummaryTexts[i]->setOrigin({gameBounds.size.x / 2.0f, gameBounds.size.y / 2.0f});
        gameSummaryTexts[i]->setPosition({centerX, startY + (i * 50.f)});
    }
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(engine->getWindow());
    backButton->update(mousePos);
}

void OverallAnalyticsScreen::render(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(brainScoreLabel);
    window.draw(brainScoreValue);
    window.draw(totalGamesText);
    
    for (int i = 0; i < 4; i++) {
        window.draw(*gameSummaryTexts[i]);
    }
    
    backButton->render(window);
}
