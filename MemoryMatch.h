#ifndef MEMORYMATCH_H
#define MEMORYMATCH_H

#include "BaseGame.h"
#include <vector>

class MemoryMatch : public BaseGame {
private:
  std::vector<int> sequence;
  bool isShowingPattern;

  void AddToSequence();

public:
  MemoryMatch(std::string difficulty, StatisticsManager *stats);
  void Update(double deltaTime) override;
  void DisplayOutput() override;
  void HandleInput() override;
};

#endif
