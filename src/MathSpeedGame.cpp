#include "MathSpeedGame.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

MathSpeedGame::MathSpeedGame(std::string difficulty, StatisticsManager *stats, SoundManager *soundMgr)
    : BaseGame(difficulty, 60.0, stats, 1, soundMgr), correct_answer(0) {
  CreateProblem(difficulty);
}

void MathSpeedGame::CreateProblem(std::string difficulty) {
  int max_num = 10;

  if (difficulty == "Medium") {
    max_num = 20;
  }
  if (difficulty == "Hard") {
    max_num = 50;
  }

  a = (rand() % max_num) + 1;
  b = (rand() % max_num) + 1;

  int op_index = rand() % 3;
  std::string op_symbol = operations_array[op_index];

  if (op_symbol == "+") {
    correct_answer = a + b;
  } else if (op_symbol == "-") {
    correct_answer = a - b;
  } else {
    correct_answer = a * b;
  }

  displaying_equation =
      std::to_string(a) + " " + op_symbol + " " + std::to_string(b) + " = ?";
}

void MathSpeedGame::Update(double deltaTime) { BaseGame::Update(deltaTime); }
