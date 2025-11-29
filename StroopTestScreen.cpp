#include "StroopTestScreen.h"
#include "Engine.h"
#include "GameSelectScreen.h"
#include <sstream>
#include <iomanip>

StroopTestScreen::StroopTestScreen(Engine* app)
    : BaseScreen(app),
      titleText(*app->getFont()),
      timerText(*app->getFont()),
      scoreText(*app->getFont()),
      instructionText(*app->getFont()),
      wordText(*app->getFont()),
      statsText(*app->getFont()),
      feedbackText(*app->getFont()),
      showFeedback(false),
      feedbackTimer(0.0f)
{
    game = new StroopTestGame("Medium", app->getStats());
    
    sf::Vector2u windowSize = app->getWindow().getSize();
    float centerX = windowSize.x / 2.0f;
    
    titleText.setString("STROOP TEST");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(2.0f);
    titleText.setStyle(sf::Text::Bold);
    
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin({titleBounds.size.x / 2.0f, titleBounds.size.y / 2.0f});
    titleText.setPosition({centerX, 40.f});
    
    timerText.setCharacterSize(22);
    timerText.setFillColor(sf::Color::White);
    
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Yellow);
    
    instructionText.setString("Click the button matching the INK COLOR");
    instructionText.setCharacterSize(18);
    instructionText.setFillColor(sf::Color(180, 180, 180));
    sf::FloatRect instrBounds = instructionText.getLocalBounds();
    instructionText.setOrigin({instrBounds.size.x / 2.0f, instrBounds.size.y / 2.0f});
    instructionText.setPosition({centerX, 85.f});
    
    wordText.setCharacterSize(60);
    wordText.setStyle(sf::Text::Bold);
    
    statsText.setCharacterSize(20);
    statsText.setFillColor(sf::Color::White);
    
    feedbackText.setCharacterSize(28);
    feedbackText.setStyle(sf::Text::Bold);
    
    float btnWidth = 120.f;
    float btnHeight = 60.f;
    float gapX = 20.f;
    float gapY = 20.f;
    float startX = centerX - btnWidth - (gapX / 2.0f);
    float startY = 500.f;
    
    redButton = new Button(
        startX, startY, btnWidth, btnHeight,
        app->getFont(),
        "RED",
        sf::Color(100, 30, 30),
        sf::Color(130, 40, 40),
        sf::Color::Red
    );
    
    blueButton = new Button(
        startX + btnWidth + gapX, startY, btnWidth, btnHeight,
        app->getFont(),
        "BLUE",
        sf::Color(30, 30, 100),
        sf::Color(40, 40, 130),
        sf::Color::Blue
    );
    
    greenButton = new Button(
        startX, startY + btnHeight + gapY, btnWidth, btnHeight,
        app->getFont(),
        "GREEN",
        sf::Color(30, 100, 30),
        sf::Color(40, 130, 40),
        sf::Color::Green
    );
    
    yellowButton = new Button(
        startX + btnWidth + gapX, startY + btnHeight + gapY, btnWidth, btnHeight,
        app->getFont(),
        "YELLOW",
        sf::Color(100, 100, 30),
        sf::Color(130, 130, 40),
        sf::Color::Yellow
    );
    
    float backBtnWidth = 120.f;
    float backBtnHeight = 45.f;
    backButton = new Button(
        centerX - (backBtnWidth / 2.0f), windowSize.y - 70.f,
        backBtnWidth, backBtnHeight,
        app->getFont(),
        "Back",
        sf::Color(70, 70, 70),
        sf::Color(100, 100, 100),
        sf::Color(200, 50, 50)
    );
}

StroopTestScreen::~StroopTestScreen() {
    delete game;
    delete redButton;
    delete blueButton;
    delete greenButton;
    delete yellowButton;
    delete backButton;
}

void StroopTestScreen::handleColorButtonClick(StroopTestGame::ColorType color) {
    if (!game->IsGameActive()) return;
    
    bool correct = game->CheckAnswer(color);
    
    if (correct) {
        feedbackText.setString("CORRECT! +100");
        feedbackText.setFillColor(sf::Color::Green);
    } else {
        feedbackText.setString("WRONG! -30");
        feedbackText.setFillColor(sf::Color::Red);
    }
    
    showFeedback = true;
    feedbackTimer = 0.0f;
    
    game->GenerateNext();
}

void StroopTestScreen::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            
            if (backButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new GameSelectScreen(engine));
                return;
            }
            
            if (game->IsGameActive()) {
                if (redButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                    handleColorButtonClick(StroopTestGame::ColorType::Red);
                } else if (blueButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                    handleColorButtonClick(StroopTestGame::ColorType::Blue);
                } else if (greenButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                    handleColorButtonClick(StroopTestGame::ColorType::Green);
                } else if (yellowButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                    handleColorButtonClick(StroopTestGame::ColorType::Yellow);
                }
            }
        }
    }
}

void StroopTestScreen::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
    
    game->Update(dt);
    
    float centerX = engine->getWindow().getSize().x / 2.0f;
    
    std::ostringstream timerStream;
    timerStream << "Time: " << std::fixed << std::setprecision(1) 
                << game->GameTimer << "s / " 
                << game->TimeLimit << "s";
    timerText.setString(timerStream.str());
    sf::FloatRect timerBounds = timerText.getLocalBounds();
    timerText.setOrigin({timerBounds.size.x / 2.0f, timerBounds.size.y / 2.0f});
    timerText.setPosition({centerX, 120.f});
    
    scoreText.setString("Score: " + std::to_string(game->currentScore));
    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin({scoreBounds.size.x / 2.0f, scoreBounds.size.y / 2.0f});
    scoreText.setPosition({centerX, 155.f});
    
    std::ostringstream statsStream;
    statsStream << "Correct: " << game->GetCorrectCount() 
                << " | Wrong: " << game->GetIncorrectCount();
    statsText.setString(statsStream.str());
    sf::FloatRect statsBounds = statsText.getLocalBounds();
    statsText.setOrigin({statsBounds.size.x / 2.0f, statsBounds.size.y / 2.0f});
    statsText.setPosition({centerX, 190.f});
    
    wordText.setString(game->GetWordText());
    wordText.setFillColor(game->GetSFMLColor());
    sf::FloatRect wordBounds = wordText.getLocalBounds();
    wordText.setOrigin({wordBounds.size.x / 2.0f, wordBounds.size.y / 2.0f});
    wordText.setPosition({centerX, 320.f});
    
    if (showFeedback) {
        feedbackTimer += dt;
        if (feedbackTimer >= 0.8f) {
            showFeedback = false;
        }
    }
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(engine->getWindow());
    redButton->update(mousePos);
    blueButton->update(mousePos);
    greenButton->update(mousePos);
    yellowButton->update(mousePos);
    backButton->update(mousePos);
}

void StroopTestScreen::render(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(timerText);
    window.draw(scoreText);
    window.draw(instructionText);
    window.draw(statsText);
    window.draw(wordText);
    
    redButton->render(window);
    blueButton->render(window);
    greenButton->render(window);
    yellowButton->render(window);
    backButton->render(window);
    
    if (showFeedback) {
        float centerX = window.getSize().x / 2.0f;
        sf::FloatRect feedbackBounds = feedbackText.getLocalBounds();
        feedbackText.setOrigin({feedbackBounds.size.x / 2.0f, feedbackBounds.size.y / 2.0f});
        feedbackText.setPosition({centerX, 420.f});
        window.draw(feedbackText);
    }
    
    if (!game->IsGameActive()) {
        sf::Text gameOverText(*engine->getFont());
        gameOverText.setString("GAME OVER!");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setStyle(sf::Text::Bold);
        
        sf::FloatRect bounds = gameOverText.getLocalBounds();
        gameOverText.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
        gameOverText.setPosition({window.getSize().x / 2.0f, 300.f});
        
        window.draw(gameOverText);
    }
}
