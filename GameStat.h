#ifndef GAMESTAT_H
#define GAMESTAT_H

#include <string>

class GameStat {
public:
  std::string gameName;
  int scores[100];
  int highScore;
  int playCount;
  int scoreCount;
};

#endif
