#include "MemoryMatchScreen.h"
#include "Engine.h"
#include "GameSelectScreen.h"
#include <iostream>
#include <sstream>

MemoryMatchScreen::MemoryMatchScreen(Engine *app)
    : BaseScreen(app), titleText(*app->getFont()), scoreText(*app->getFont()),
      instructionText(*app->getFont()), sequenceDisplayText(*app->getFont()),
      inputPromptText(*app->getFont()), inputText(*app->getFont()),
      feedbackText(*app->getFont()), isShowingSequence(true), sequenceIndex(0),
      sequenceTimer(0.0f), userSequenceIndex(0), showFeedback(false), feedbackTimer(0.0f)
{
  game = new MemoryMatch("Easy", app->getStats(), app->getSoundManager());

  sf::Vector2u windowSize = app->getWindow().getSize();
  float centerX = windowSize.x / 2.0f;

  titleText.setString("MEMORY MATCH");
  titleText.setCharacterSize(40);
  titleText.setFillColor(sf::Color::Cyan);
  titleText.setStyle(sf::Text::Bold);
  sf::FloatRect titleBounds = titleText.getLocalBounds();
  titleText.setOrigin({titleBounds.size.x / 2.0f, titleBounds.size.y / 2.0f});
  titleText.setPosition({centerX, 80.f});

  scoreText.setCharacterSize(28);
  scoreText.setFillColor(sf::Color::Green);
  scoreText.setPosition({50.f, 150.f});

  instructionText.setString("Watch the sequence...");
  instructionText.setCharacterSize(24);
  instructionText.setFillColor(sf::Color::Yellow);
  sf::FloatRect instBounds = instructionText.getLocalBounds();
  instructionText.setOrigin({instBounds.size.x / 2.0f, instBounds.size.y / 2.0f});
  instructionText.setPosition({centerX, 200.f});

  sequenceDisplayText.setCharacterSize(120);
  sequenceDisplayText.setFillColor(sf::Color::White);
  sequenceDisplayText.setStyle(sf::Text::Bold);

  inputPromptText.setString("Type the sequence:");
  inputPromptText.setCharacterSize(24);
  inputPromptText.setFillColor(sf::Color::White);
  inputPromptText.setPosition({centerX - 100.f, 450.f});

  inputText.setCharacterSize(32);
  inputText.setFillColor(sf::Color::Cyan);
  inputText.setPosition({centerX - 100.f, 490.f});

  feedbackText.setCharacterSize(36);
  feedbackText.setStyle(sf::Text::Bold);
  feedbackText.setPosition({centerX - 80.f, 560.f});

  float backBtnWidth = 150.f;
  float backBtnHeight = 50.f;
  backButton = new Button(
      centerX - (backBtnWidth / 2.0f), 850.f, backBtnWidth, backBtnHeight,
      app->getFont(), "Back", sf::Color(70, 70, 70), sf::Color(100, 100, 100),
      sf::Color(200, 50, 50), app->getSoundManager());
}

MemoryMatchScreen::~MemoryMatchScreen() {
  delete game;
  delete backButton;
}

void MemoryMatchScreen::handleInput(const sf::Event &event,
                                     sf::RenderWindow &window) {
  if (const auto *mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseButton->button == sf::Mouse::Button::Left) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      if (backButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
        engine->switchScreen(new GameSelectScreen(engine));
      }
    }
  }

  if (isShowingSequence || !game->IsGameActive()) {
    return;
  }

  if (const auto *keyPress = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPress->code == sf::Keyboard::Key::Enter) {
      if (!userInput.empty()) {
        try {
          int num = std::stoi(userInput);
          
          if (userSequenceIndex < game->sequence.size()) {
            if (num == game->sequence[userSequenceIndex]) {
              feedbackText.setString("Correct!");
              feedbackText.setFillColor(sf::Color::Green);
              showFeedback = true;
              feedbackTimer = 0.0f;
              userSequenceIndex++;
              
              if (userSequenceIndex >= game->sequence.size()) {
                game->AddScore(100);
                game->AddToSequence();
                isShowingSequence = true;
                sequenceIndex = 0;
                sequenceTimer = 0.0f;
                userSequenceIndex = 0;
                instructionText.setString("Watch the sequence...");
              }
            } else {
              feedbackText.setString("Wrong! Game Over");
              feedbackText.setFillColor(sf::Color::Red);
              showFeedback = true;
              feedbackTimer = 0.0f;
              game->EndGame();
            }
          }
          
          userInput.clear();
        } catch (...) {
          userInput.clear();
        }
      }
    } else if (keyPress->code == sf::Keyboard::Key::Backspace) {
      if (!userInput.empty()) {
        userInput.pop_back();
      }
    }
  }

  if (const auto *textEntered = event.getIf<sf::Event::TextEntered>()) {
    if (!isShowingSequence && game->IsGameActive()) {
      char c = static_cast<char>(textEntered->unicode);
      if (c >= '0' && c <= '9') {
        userInput += c;
      }
    }
  }
}

void MemoryMatchScreen::update(sf::Time deltaTime) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(engine->getWindow());
  backButton->update(mousePos);

  std::ostringstream scoreStream;
  scoreStream << "Score: " << game->currentScore;
  scoreText.setString(scoreStream.str());

  if (isShowingSequence && game->IsGameActive()) {
    sequenceTimer += deltaTime.asSeconds();
    
    if (sequenceIndex == 0 && sequenceTimer < 1.0f) {
      return;
    }
    
    if (sequenceIndex < game->sequence.size()) {
      int displayTime = (sequenceIndex == 0) ? 1 : 0;
      float totalTimePerNumber = 1.2f;
      
      if (sequenceTimer >= displayTime + (sequenceIndex * totalTimePerNumber) + totalTimePerNumber) {
        sequenceIndex++;
      }
    } else {
      if (sequenceTimer >= 1.0f + (game->sequence.size() * 1.2f) + 0.5f) {
        isShowingSequence = false;
        userSequenceIndex = 0;
        instructionText.setString("Now type the numbers!");
      }
    }
  }

  inputText.setString(userInput + "_");

  if (showFeedback) {
    feedbackTimer += deltaTime.asSeconds();
    if (feedbackTimer > 0.6f) {
      showFeedback = false;
      feedbackTimer = 0.0f;
    }
  }
}

void MemoryMatchScreen::render(sf::RenderWindow &window) {
  window.draw(titleText);
  window.draw(scoreText);
  window.draw(instructionText);

  if (isShowingSequence && game->IsGameActive()) {
    int displayIndex = sequenceIndex;
    if (sequenceTimer >= 1.0f && displayIndex < game->sequence.size()) {
      float timeIntoSequence = sequenceTimer - 1.0f;
      int currentNumIndex = (int)(timeIntoSequence / 1.2f);
      
      if (currentNumIndex < game->sequence.size()) {
        float timeInCurrentNum = timeIntoSequence - (currentNumIndex * 1.2f);
        
        if (timeInCurrentNum < 1.0f) {
          std::ostringstream seqStream;
          seqStream << game->sequence[currentNumIndex];
          sequenceDisplayText.setString(seqStream.str());
          
          sf::FloatRect seqBounds = sequenceDisplayText.getLocalBounds();
          sequenceDisplayText.setOrigin({seqBounds.size.x / 2.0f, seqBounds.size.y / 2.0f});
          sequenceDisplayText.setPosition({270.f, 350.f});
          window.draw(sequenceDisplayText);
        }
      }
    }
  } else if (game->IsGameActive()) {
    window.draw(inputPromptText);
    window.draw(inputText);
    
    if (showFeedback) {
      window.draw(feedbackText);
    }
  }

  if (!game->IsGameActive()) {
    sf::Text gameOverText(*engine->getFont());
    gameOverText.setString("GAME OVER!");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
    gameOverText.setPosition({270.f, 300.f});
    window.draw(gameOverText);
  }

  backButton->render(window);
}
