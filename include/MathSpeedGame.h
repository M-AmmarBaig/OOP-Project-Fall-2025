#ifndef MATHSPEEDGAME_H
#define MATHSPEEDGAME_H

#include "BaseGame.h"
#include <string>

class MathSpeedGame : public BaseGame {
public:
  int a;
  int b;
  std::string displaying_equation;
  std::string operations_array[3] = {"+", "-", "*"};
  int correct_answer;

  void CreateProblem(std::string difficulty);
  MathSpeedGame(std::string difficulty, StatisticsManager *stats, SoundManager *soundMgr);
  void Update(double deltaTime) override;
};

#endif
