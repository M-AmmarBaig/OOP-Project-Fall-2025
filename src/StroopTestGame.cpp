#include "StroopTestGame.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

StroopTestGame::StroopTestGame(std::string difficulty, StatisticsManager* stats, SoundManager* soundMgr)
    : BaseGame(difficulty, 60.0, stats, 3, soundMgr), 
      correctCount(0),
      incorrectCount(0)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    generateNewTrial();
    StartTimer();
}

std::string StroopTestGame::colorToString(ColorType color) {
    switch (color) {
        case ColorType::Red: return "RED";
        case ColorType::Blue: return "BLUE";
        case ColorType::Green: return "GREEN";
        case ColorType::Yellow: return "YELLOW";
        default: return "RED";
    }
}

sf::Color StroopTestGame::GetSFMLColor() const {
    switch (displayColor) {
        case ColorType::Red: return sf::Color::Red;
        case ColorType::Blue: return sf::Color::Blue;
        case ColorType::Green: return sf::Color::Green;
        case ColorType::Yellow: return sf::Color::Yellow;
        default: return sf::Color::Red;
    }
}

void StroopTestGame::generateNewTrial() {
    int wordIndex = rand() % 4;
    ColorType wordColor = static_cast<ColorType>(wordIndex);
    wordText = colorToString(wordColor);

    bool makeCongruent = false;
    
    std::string diff = GetDifficulty();
    if (diff == "Easy") {
        makeCongruent = (rand() % 100) < 60;  
    } else if (diff == "Medium") {
        makeCongruent = (rand() % 100) < 40;  
    } else { 
        makeCongruent = (rand() % 100) < 20;  
    }
    
    if (makeCongruent) {
        displayColor = wordColor;
    } else {
        int colorIndex;
        do {
            colorIndex = rand() % 4;
        } while (colorIndex == wordIndex);
        displayColor = static_cast<ColorType>(colorIndex);
    }
    
    correctAnswer = displayColor;  
}

void StroopTestGame::Update(double deltaTime) {
    if (!IsGameActive()) return;
    UpdateTimer(deltaTime);
}

bool StroopTestGame::CheckAnswer(ColorType selectedColor) {
    if (!IsGameActive()) return false;
    
    if (selectedColor == correctAnswer) {
        correctCount++;
        AddScore(100);
        return true;
    } else {
        incorrectCount++;
        AddScore(-30);
        return false;
    }
}

void StroopTestGame::GenerateNext() {
    generateNewTrial();
}


