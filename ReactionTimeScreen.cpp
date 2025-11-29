#include "ReactionTimeScreen.h"
#include "Engine.h"
#include "GameSelectScreen.h"
#include <sstream>
#include <iomanip>

ReactionTimeScreen::ReactionTimeScreen(Engine* app)
    : BaseScreen(app),
      titleText(*app->getFont()),
      timerText(*app->getFont()),
      scoreText(*app->getFont()),
      instructionText(*app->getFont()),
      statsText(*app->getFont()),
      reactionText(*app->getFont()),
      showReactionFeedback(false),
      reactionFeedbackTimer(0.0f),
      lastReactionTime(0.0f)
{
    game = new ReactionTimeGame("Medium", app->getStats());
    
    sf::Vector2u windowSize = app->getWindow().getSize();
    float centerX = windowSize.x / 2.0f;
    
    game->SetSpawnBounds(0.0f, static_cast<float>(windowSize.x), 
                        150.0f, static_cast<float>(windowSize.y));
    
    titleText.setString("REACTION TIME CHALLENGE");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(2.0f);
    titleText.setStyle(sf::Text::Bold);
    
    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
    titleText.setPosition({centerX, 50.f});
    
    timerText.setCharacterSize(28);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition({50.f, 100.f});
    
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition({50.f, 140.f});
    
    instructionText.setString("Click the targets as fast as you can!");
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(sf::Color(150, 150, 150));
    textRect = instructionText.getLocalBounds();
    instructionText.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
    instructionText.setPosition({centerX, 120.f});
    
    statsText.setCharacterSize(24);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition({windowSize.x - 300.f, 100.f});
    
    reactionText.setCharacterSize(32);
    reactionText.setFillColor(sf::Color::Green);
    reactionText.setStyle(sf::Text::Bold);
    
    targetCircle.setFillColor(sf::Color::Red);
    targetCircle.setOrigin({game->GetTargetRadius(), game->GetTargetRadius()});
    
    float backBtnWidth = 150.f;
    float backBtnHeight = 50.f;
    backButton = new Button(
        30.f, windowSize.y - 80.f, backBtnWidth, backBtnHeight,
        app->getFont(),
        "Back",
        sf::Color(70, 70, 70),
        sf::Color(100, 100, 100),
        sf::Color(200, 50, 50)
    );
}

ReactionTimeScreen::~ReactionTimeScreen() {
    delete game;
    delete backButton;
}

void ReactionTimeScreen::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            
            if (backButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
                engine->switchScreen(new GameSelectScreen(engine));
                return;
            }
            
            if (game->IsGameActive()) {
                float reactionTime = 0.0f;
                if (game->CheckClick(static_cast<float>(mousePos.x), 
                                    static_cast<float>(mousePos.y), 
                                    reactionTime)) {
                    showReactionFeedback = true;
                    reactionFeedbackTimer = 0.0f;
                    lastReactionTime = reactionTime;
                }
            }
        }
    }
}

void ReactionTimeScreen::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
    
    game->Update(dt);
    
    std::ostringstream timerStream;
    timerStream << "Time: " << std::fixed << std::setprecision(1) 
                << game->GameTimer << "s / " 
                << game->TimeLimit << "s";
    timerText.setString(timerStream.str());
    
    scoreText.setString("Score: " + std::to_string(game->currentScore));
    
    std::ostringstream statsStream;
    statsStream << "Clicked: " << game->GetTargetsClicked() << "\n"
                << "Missed: " << game->GetTargetsMissed();
    statsText.setString(statsStream.str());
    
    if (game->IsTargetActive()) {
        targetCircle.setRadius(game->GetTargetRadius());
        targetCircle.setOrigin({game->GetTargetRadius(), game->GetTargetRadius()});
        targetCircle.setPosition(game->GetTargetPosition());
    }
    
    if (showReactionFeedback) {
        reactionFeedbackTimer += dt;
        if (reactionFeedbackTimer >= 1.0f) {
            showReactionFeedback = false;
        }
    }
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(engine->getWindow());
    backButton->update(mousePos);
}

void ReactionTimeScreen::render(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(timerText);
    window.draw(scoreText);
    window.draw(instructionText);
    window.draw(statsText);
    
    if (game->IsTargetActive()) {
        window.draw(targetCircle);
    }
    
    if (showReactionFeedback) {
        std::ostringstream reactionStream;
        reactionStream << std::fixed << std::setprecision(3) 
                      << lastReactionTime << "s!";
        reactionText.setString(reactionStream.str());
        
        sf::FloatRect bounds = reactionText.getLocalBounds();
        reactionText.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
        reactionText.setPosition({window.getSize().x / 2.0f, 450.f});
        
        window.draw(reactionText);
    }
    
    backButton->render(window);
    
    if (!game->IsGameActive()) {
        sf::Text gameOverText(*engine->getFont());
        gameOverText.setString("GAME OVER!");
        gameOverText.setCharacterSize(60);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setStyle(sf::Text::Bold);
        
        sf::FloatRect bounds = gameOverText.getLocalBounds();
        gameOverText.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
        gameOverText.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});
        
        window.draw(gameOverText);
    }
}
