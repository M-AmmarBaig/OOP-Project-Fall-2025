#include "OverallAnalyticsScreen.h"
#include "Engine.h"
#include "AnalyticsMenuScreen.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

OverallAnalyticsScreen::OverallAnalyticsScreen(Engine* app)
    : BaseScreen(app),
      stats(app->getStats()),
      titleText(*app->getFont()),
      brainScoreLabel(*app->getFont()),
      brainScoreValue(*app->getFont()),
      totalGamesText(*app->getFont())
{
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
    
    const char* gameNames[] = {"Memory\nMatch", "Math\nSpeed", "Reaction\nTime", "Stroop\nTest"};
    sf::Color barColors[] = {
        sf::Color(150, 100, 200),  // Purple
        sf::Color(200, 150, 50),   // Orange
        sf::Color(50, 200, 100),   // Green
        sf::Color(200, 100, 200)   // Pink
    };
    
    float barWidth = 60.f;
    float barSpacing = 90.f;
    float chartStartX = centerX - (barSpacing * 1.5f);
    float chartY = 480.f;
    
    for (int i = 0; i < 4; i++) {
        float barX = chartStartX + (i * barSpacing);
        
        barBackgrounds[i].setSize({barWidth, 200.f});
        barBackgrounds[i].setPosition({barX, chartY});
        barBackgrounds[i].setFillColor(sf::Color(40, 40, 40));
        barBackgrounds[i].setOutlineColor(sf::Color(80, 80, 80));
        barBackgrounds[i].setOutlineThickness(2.f);
        
        bars[i].setSize({barWidth, 0.f});
        bars[i].setPosition({barX, chartY + 200.f});
        bars[i].setFillColor(barColors[i]);
        
        gameNameLabels[i] = new sf::Text(*app->getFont());
        gameNameLabels[i]->setString(gameNames[i]);
        gameNameLabels[i]->setCharacterSize(14);
        gameNameLabels[i]->setFillColor(sf::Color::White);
        sf::FloatRect nameBounds = gameNameLabels[i]->getLocalBounds();
        gameNameLabels[i]->setOrigin({nameBounds.size.x / 2.0f, 0.f});
        gameNameLabels[i]->setPosition({barX + barWidth / 2.0f, chartY + 210.f});
        
        scoreValueLabels[i] = new sf::Text(*app->getFont());
        scoreValueLabels[i]->setCharacterSize(16);
        scoreValueLabels[i]->setFillColor(sf::Color::White);
        scoreValueLabels[i]->setStyle(sf::Text::Bold);
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
        delete gameNameLabels[i];
        delete scoreValueLabels[i];
    }
    delete backButton;
}

int OverallAnalyticsScreen::calculateBrainScore() {
    int totalScore = 0;
    int gamesWithData = 0;
    
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
    
    std::ostringstream totalStream;
    totalStream << "Total Games Played: " << stats->GetGamesPlayedCount();
    totalGamesText.setString(totalStream.str());
    
    sf::FloatRect totalBounds = totalGamesText.getLocalBounds();
    totalGamesText.setOrigin({totalBounds.size.x / 2.0f, totalBounds.size.y / 2.0f});
    totalGamesText.setPosition({centerX, 220.f});
    
    // Update bar chart
    float maxScore = 1.0f;  // Prevent division by zero
    for (int i = 0; i < 4; i++) {
        float score = static_cast<float>(stats->GetBestScore(i));
        if (score > maxScore) {
            maxScore = score;
        }
    }
    
    float maxBarHeight = 200.f;
    float barWidth = 60.f;
    float barSpacing = 90.f;
    float chartStartX = centerX - (barSpacing * 1.5f);
    float chartY = 480.f;
    
    for (int i = 0; i < 4; i++) {
        float score = static_cast<float>(stats->GetBestScore(i));
        float normalizedHeight = (score / maxScore) * maxBarHeight;
        
        if (normalizedHeight < 5.f && score > 0) {
            normalizedHeight = 5.f;  
        }
        
        bars[i].setSize({barWidth, normalizedHeight});
        bars[i].setPosition({chartStartX + (i * barSpacing), chartY + maxBarHeight - normalizedHeight});
        
        std::ostringstream valueStream;
        valueStream << static_cast<int>(score);
        scoreValueLabels[i]->setString(valueStream.str());
        
        sf::FloatRect valueBounds = scoreValueLabels[i]->getLocalBounds();
        scoreValueLabels[i]->setOrigin({valueBounds.size.x / 2.0f, valueBounds.size.y});
        scoreValueLabels[i]->setPosition({chartStartX + (i * barSpacing) + barWidth / 2.0f, chartY + maxBarHeight - normalizedHeight - 5.f});
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
        window.draw(barBackgrounds[i]);
        window.draw(bars[i]);
        window.draw(*gameNameLabels[i]);
        window.draw(*scoreValueLabels[i]);
    }
    
    backButton->render(window);
}
