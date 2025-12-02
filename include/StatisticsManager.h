#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include "GameStat.h"
#include <string>

class StatisticsManager {
private:
  GameStat allGames[5];
  std::string SaveFileName;
  int totalGamesPlayed;

public:
  StatisticsManager(std::string saveFileName = "game_stats.txt");
  bool ReadFromFile();
  bool SaveToFile();
  void SaveScore(int gameindex, int score);
  double GetBestScore(int GameIndex);
  int GetGamesPlayedCount();
  int GetGameSpecificPlayCount(int GameIndex);
  std::string GetGameName(int GameIndex);
  double GetAverageScore(int GameIndex);
};

#endif
