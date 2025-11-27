#include "Engine.h"
#include <cstdlib>
#include <ctime>

int main() {
  srand(time(0));
  Engine engine;
  engine.Run();
  return 0;
}
