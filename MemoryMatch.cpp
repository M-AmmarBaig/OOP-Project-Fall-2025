#include "MemoryMatch.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

MemoryMatch::MemoryMatch(std::string difficulty, StatisticsManager *stats, SoundManager *soundMgr)
    : BaseGame(difficulty, 0.0, stats, 0, soundMgr) {
  isShowingPattern = true;
  AddToSequence();
  AddToSequence();
  AddToSequence();
}

void MemoryMatch::AddToSequence() {
  int nextNum = (rand() % 4) + 1;
  sequence.push_back(nextNum);
}

void MemoryMatch::Update(double deltaTime) { BaseGame::Update(deltaTime); }

void MemoryMatch::DisplayOutput() {
  if (isShowingPattern == true) {
    system("cls");
    std::cout << "Memorize This Sequence..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    for (int i = 0; i < sequence.size(); i++) {
      system("cls");
      std::cout << "\n\n   " << sequence[i] << "   \n\n";
      std::this_thread::sleep_for(std::chrono::seconds(1));
      system("cls");
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    isShowingPattern = false;
  } else {
    std::cout << "Welcome To Memory Match" << std::endl;
    std::cout << "Current difficulty: " << GetDifficulty() << std::endl;
    std::cout << "YOUR TURN! Type the numbers..." << std::endl;
  }
}

void MemoryMatch::HandleInput() {
  if (isShowingPattern == true) {
    return;
  } else {
    for (int i = 0; i < sequence.size(); i++) {
      int user_guess = 0;
      std::cin >> user_guess;

      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid Input" << std::endl;
        EndGame();
        return;
      }

      if (user_guess == sequence[i]) {
        std::cout << "Matched" << std::endl;
      } else {
        std::cout << "Game Over!" << std::endl;
        EndGame();
        return;
      }
    }
    AddScore(100);
    AddToSequence();
    isShowingPattern = true;
  }
}
