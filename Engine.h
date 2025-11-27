#ifndef ENGINE_H
#define ENGINE_H

#include "StatisticsManager.h"

class Engine {
private:
  StatisticsManager statsManager;

  void StartGameSession();
  void ShowAnalytics();

public:
  Engine();
  void Run();
};

#endif
