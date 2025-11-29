#ifndef BASEGAME_H
#define BASEGAME_H

#include "StatisticsManager.h"
#include "SoundManager.h"
#include <string>

class BaseGame {
private:
  double ScoreMultiplier;
  bool IsPaused;
  bool IsGameOver;
  bool TimerActive;
  std::string difficultyLevel;
  int gameIndex;

public:
  StatisticsManager *InternalGameStatistics;
  SoundManager *soundManager;
  int currentScore;
  double GameTimer;
  double TimeLimit;

  BaseGame();
  BaseGame(std::string difficulty, double TimeLimit,
           StatisticsManager *statsManager, int GameIndex, SoundManager *soundMgr);

  void AddScore(int Points);
  void StartTimer();
  void UpdateTimer(double ChangeInTime);
  void SetDifficulty(std::string GivenDifficulty);
  std::string GetDifficulty();
  void EndGame();
  bool IsGameActive();

  virtual void HandleInput() = 0;
  virtual void Update(double TimeChange);
  virtual void DisplayOutput() = 0;
  virtual ~BaseGame();
};

#endif
