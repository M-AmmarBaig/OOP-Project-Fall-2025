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
