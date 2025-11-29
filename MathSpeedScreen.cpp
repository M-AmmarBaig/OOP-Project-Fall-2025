#include "MathSpeedScreen.h"
#include "Engine.h"
#include "GameSelectScreen.h"
#include <iostream>
#include <sstream>

MathSpeedScreen::MathSpeedScreen(Engine *app)
    : BaseScreen(app), titleText(*app->getFont()), timerText(*app->getFont()),
      scoreText(*app->getFont()), equationText(*app->getFont()),
      inputPromptText(*app->getFont()), inputText(*app->getFont()),
      feedbackText(*app->getFont()), showFeedback(false), feedbackTimer(0.0f)
{
  game = new MathSpeedGame("Easy", app->getStats());
  game->StartTimer();

  sf::Vector2u windowSize = app->getWindow().getSize();
  float centerX = windowSize.x / 2.0f;

  titleText.setString("MATH SPEED");
  titleText.setCharacterSize(40);
  titleText.setFillColor(sf::Color::Cyan);
  titleText.setStyle(sf::Text::Bold);
  sf::FloatRect titleBounds = titleText.getLocalBounds();
  titleText.setOrigin({titleBounds.size.x / 2.0f, titleBounds.size.y / 2.0f});
  titleText.setPosition({centerX, 80.f});

  timerText.setCharacterSize(28);
  timerText.setFillColor(sf::Color::Yellow);
  timerText.setPosition({50.f, 150.f});

  scoreText.setCharacterSize(28);
  scoreText.setFillColor(sf::Color::Green);
  scoreText.setPosition({50.f, 190.f});

  equationText.setCharacterSize(48);
  equationText.setFillColor(sf::Color::White);
  equationText.setStyle(sf::Text::Bold);
  equationText.setPosition({centerX - 100.f, 320.f});

  inputPromptText.setString("Your Answer:");
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

MathSpeedScreen::~MathSpeedScreen() {
  delete game;
  delete backButton;
}

void MathSpeedScreen::handleInput(const sf::Event &event,
                                   sf::RenderWindow &window) {
  if (const auto *mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseButton->button == sf::Mouse::Button::Left) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      if (backButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
        engine->switchScreen(new GameSelectScreen(engine));
      }
    }
  }

  if (const auto *keyPress = event.getIf<sf::Event::KeyPressed>()) {
    if (!game->IsGameActive()) {
      return;
    }

    if (keyPress->code == sf::Keyboard::Key::Enter) {
      if (!userInput.empty()) {
        try {
          int answer = std::stoi(userInput);
          
          if (answer == game->correct_answer) {
            game->AddScore(100);
            feedbackText.setString("Correct! +100");
            feedbackText.setFillColor(sf::Color::Green);
          } else {
            game->AddScore(-20);
            feedbackText.setString("Wrong! -20");
            feedbackText.setFillColor(sf::Color::Red);
          }
          
          game->CreateProblem(game->GetDifficulty());
          userInput.clear();
          showFeedback = true;
          feedbackTimer = 0.0f;
          
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
    if (game->IsGameActive()) {
      char c = static_cast<char>(textEntered->unicode);
      if (c >= '0' && c <= '9') {
        userInput += c;
      } else if (c == '-' && userInput.empty()) {
        userInput += c;
      }
    }
  }
}

void MathSpeedScreen::update(sf::Time deltaTime) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(engine->getWindow());
  backButton->update(mousePos);

  if (game->IsGameActive()) {
    game->Update(deltaTime.asSeconds());
  }

  double remaining = game->TimeLimit - game->GameTimer;
  if (remaining < 0)
    remaining = 0;
  
  std::ostringstream timerStream;
  timerStream << "Time: " << (int)remaining << "s";
  timerText.setString(timerStream.str());

  std::ostringstream scoreStream;
  scoreStream << "Score: " << game->currentScore;
  scoreText.setString(scoreStream.str());

  inputText.setString(userInput + "_");

  if (showFeedback) {
    feedbackTimer += deltaTime.asSeconds();
    if (feedbackTimer > 0.8f) {
      showFeedback = false;
      feedbackTimer = 0.0f;
    }
  }
}

void MathSpeedScreen::render(sf::RenderWindow &window) {
  window.draw(titleText);
  window.draw(timerText);
  window.draw(scoreText);

  std::ostringstream eqStream;
  eqStream << game->a << " " << game->operations_array[0] << " " << game->b << " = ?";
  
  int op_index = 0;
  if (game->correct_answer == game->a + game->b) {
    op_index = 0;
  } else if (game->correct_answer == game->a - game->b) {
    op_index = 1;
  } else {
    op_index = 2;
  }
  
  eqStream.str("");
  eqStream << game->a << " " << game->operations_array[op_index] << " " << game->b << " = ?";
  equationText.setString(eqStream.str());
  
  window.draw(equationText);
  window.draw(inputPromptText);
  window.draw(inputText);

  if (showFeedback) {
    window.draw(feedbackText);
  }

  if (!game->IsGameActive()) {
    sf::Text gameOverText(*engine->getFont());
    gameOverText.setString("GAME OVER!");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
    gameOverText.setPosition({270.f, 250.f});
    window.draw(gameOverText);
  }

  backButton->render(window);
}
