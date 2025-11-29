#ifndef STROOPTESTGAME_H
#define STROOPTESTGAME_H

#include "BaseGame.h"
#include <SFML/Graphics/Color.hpp>
#include <string>

class StroopTestGame : public BaseGame {
public:
    enum class ColorType {
        Red,
        Blue,
        Green,
        Yellow
    };

private:
    std::string wordText;
    ColorType displayColor;
    ColorType correctAnswer;
    int correctCount;
    int incorrectCount;
    
    void generateNewTrial();
    std::string colorToString(ColorType color);

public:
    StroopTestGame(std::string difficulty, StatisticsManager* stats);
    
    void Update(double deltaTime) override;
    void DisplayOutput() override;
    void HandleInput() override;
    
    bool CheckAnswer(ColorType selectedColor);
    void GenerateNext();
    
    std::string GetWordText() const { return wordText; }
    ColorType GetDisplayColor() const { return displayColor; }
    sf::Color GetSFMLColor() const;
    int GetCorrectCount() const { return correctCount; }
    int GetIncorrectCount() const { return incorrectCount; }
};

#endif
