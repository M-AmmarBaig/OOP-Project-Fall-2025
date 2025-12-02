#ifndef MEMORYMATCH_H
#define MEMORYMATCH_H

#include "BaseGame.h"
#include <vector>

class MemoryMatch : public BaseGame {
public:
  std::vector<int> sequence;
  bool isShowingPattern;

  void AddToSequence();
  MemoryMatch(std::string difficulty, StatisticsManager *stats, SoundManager *soundMgr);
  void Update(double deltaTime) override;
};

#endif
