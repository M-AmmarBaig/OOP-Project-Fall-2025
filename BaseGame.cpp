#include "BaseGame.h"
#include <iostream>

BaseGame::BaseGame()
    : currentScore(0), GameTimer(0.0), TimeLimit(0.0), ScoreMultiplier(1.0),
      IsPaused(false), IsGameOver(false), TimerActive(false),
      difficultyLevel("Easy"), InternalGameStatistics(nullptr), gameIndex(0) {}

BaseGame::BaseGame(std::string difficulty, double TimeLimit,
                   StatisticsManager *statsManager, int GameIndex)
    : currentScore(0), GameTimer(0.0), TimeLimit(TimeLimit), IsPaused(false),
      IsGameOver(false), TimerActive(false), difficultyLevel(difficulty),
      InternalGameStatistics(statsManager), gameIndex(GameIndex) {
  SetDifficulty(difficulty);
}

void BaseGame::AddScore(int Points) {
  if (Points < 0 && currentScore < -1 * Points) {
    currentScore = 0;
    return;
  }
  currentScore += Points;
}

void BaseGame::StartTimer() {
  GameTimer = 0.0;
  TimerActive = true;
}

void BaseGame::UpdateTimer(double ChangeInTime) {
  if (TimerActive && !IsPaused) {
    GameTimer += ChangeInTime;
    if (TimeLimit > 0.0 && GameTimer >= TimeLimit) {
      EndGame();
    }
  }
}

void BaseGame::SetDifficulty(std::string GivenDifficulty) {
  difficultyLevel = GivenDifficulty;
  if (GivenDifficulty == "Easy") {
    ScoreMultiplier = 1.0;
  } else if (GivenDifficulty == "Medium") {
    ScoreMultiplier = 1.5;
  } else if (GivenDifficulty == "Hard") {
    ScoreMultiplier = 2.0;
  } else {
    ScoreMultiplier = 1.0;
    difficultyLevel = "Easy";
  }
}

std::string BaseGame::GetDifficulty() { return difficultyLevel; }

void BaseGame::EndGame() {
  IsGameOver = true;
  TimerActive = false;
  std::cout << "Game Over! Final Score: " << currentScore << std::endl;
  if (InternalGameStatistics != nullptr) {
    InternalGameStatistics->SaveScore(gameIndex, currentScore);
  }
}

bool BaseGame::IsGameActive() { return !IsPaused && !IsGameOver; }

void BaseGame::Update(double TimeChange) { UpdateTimer(TimeChange); }

BaseGame::~BaseGame() {}
