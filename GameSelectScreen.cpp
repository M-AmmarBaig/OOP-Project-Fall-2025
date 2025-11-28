#include "GameSelectScreen.h"
#include "Engine.h"
#include "MainMenuScreen.h"
#include <iostream>

GameSelectScreen::GameSelectScreen(Engine *app)
    : BaseScreen(app), titleText(*app->getFont())
{
  sf::Vector2u windowSize = app->getWindow().getSize();
  float centerX = windowSize.x / 2.0f;

  titleText.setString("SELECT A GAME");
  titleText.setCharacterSize(48);
  titleText.setFillColor(sf::Color::Cyan);
  titleText.setOutlineColor(sf::Color::Black);
  titleText.setOutlineThickness(2.0f);
  titleText.setStyle(sf::Text::Bold);

  sf::FloatRect textRect = titleText.getLocalBounds();
  titleText.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
  titleText.setPosition({centerX, 150.f});

  float btnWidth = 320.f;
  float btnHeight = 80.f;
  float btnX = centerX - (btnWidth / 2.0f);
  float startY = 350.f;
  float gap = 120.f;

  memoryMatchButton = new Button(
      btnX, startY, btnWidth, btnHeight, 
      app->getFont(),
      "Memory Match", 
      sf::Color(70, 70, 70),
      sf::Color(100, 100, 100), 
      sf::Color(150, 100, 200));  

  mathSpeedButton = new Button(
      btnX, startY + gap, btnWidth, btnHeight, 
      app->getFont(),
      "Math Speed", 
      sf::Color(70, 70, 70),
      sf::Color(100, 100, 100), 
      sf::Color(200, 150, 50));  


  float backBtnWidth = 200.f;
  float backBtnHeight = 60.f;
  float backBtnX = centerX - (backBtnWidth / 2.0f);
  
  backButton = new Button(
      backBtnX, startY + (gap * 2.5f), backBtnWidth, backBtnHeight,
      app->getFont(),
      "Back", 
      sf::Color(70, 70, 70),
      sf::Color(100, 100, 100), 
      sf::Color(200, 50, 50)); 
}

GameSelectScreen::~GameSelectScreen() {
  delete memoryMatchButton;
  delete mathSpeedButton;
  delete backButton;
}

void GameSelectScreen::handleInput(const sf::Event &event,
                                 sf::RenderWindow &window) {
  if (const auto *mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseButton->button == sf::Mouse::Button::Left) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);

      if (memoryMatchButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
        std::cout << "Memory Match selected (not yet implemented)..." << std::endl;
        // engine->switchScreen(new MemoryMatchScreen(engine));
      }
      
      if (mathSpeedButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
        std::cout << "Math Speed selected (not yet implemented)..." << std::endl;
        // engine->switchScreen(new MathSpeedScreen(engine));
      }
      
     
      if (backButton->isClicked(mousePos, sf::Mouse::Button::Left)) {
        std::cout << "Returning to main menu..." << std::endl;
        engine->switchScreen(new MainMenuScreen(engine));
      }
    }
  }
}

void GameSelectScreen::update(sf::Time deltaTime) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(engine->getWindow());
  memoryMatchButton->update(mousePos);
  mathSpeedButton->update(mousePos);
  backButton->update(mousePos);
}

void GameSelectScreen::render(sf::RenderWindow &window) {
  window.draw(titleText);
  memoryMatchButton->render(window);
  mathSpeedButton->render(window);
  backButton->render(window);
}
