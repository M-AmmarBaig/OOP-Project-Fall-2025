#include "MathSpeedGame.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

MathSpeedGame::MathSpeedGame(std::string difficulty, StatisticsManager *stats)
    : BaseGame(difficulty, 60.0, stats, 1), correct_answer(0) {
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

void MathSpeedGame::DisplayOutput() {
  system("cls");
  std::cout << "MATH SPEED GAME" << std::endl;
  double remaining = TimeLimit - GameTimer;
  if (remaining < 0)
    remaining = 0;
  std::cout << "Time: " << (int)remaining << " seconds" << std::endl;
  std::cout << "Score: " << currentScore << std::endl;

  std::cout << "\nSolve: " << displaying_equation << "\n" << std::endl;
  std::cout << "Answer: ";
}

void MathSpeedGame::HandleInput() {
  int user_input;
  std::cin >> user_input;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    return;
  }

  if (user_input == correct_answer) {
    std::cout << "Correct!" << std::endl;
    AddScore(100);
    CreateProblem(GetDifficulty());
  } else {
    std::cout << "Wrong!" << std::endl;
    AddScore(-20);
    CreateProblem(GetDifficulty());
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(800));
}
