#include "Engine.h"
#include "MathSpeedGame.h"
#include "MemoryMatch.h"
#include <chrono>
#include <iostream>

Engine::Engine() : statsManager("game_data.txt") { statsManager.ReadFromFile(); }

void Engine::StartGameSession() {
  std::cout << "Select Difficulty (Easy, Medium, Hard): ";
  std::string diff;
  std::cin >> diff;

  MathSpeedGame game(diff, &statsManager); // we can change this
  game.StartTimer();

  // MemoryMatch game(diff, &statsManager); // we can change this
  // game.StartTimer();

  auto lastTime = std::chrono::steady_clock::now();

  while (game.IsGameActive()) {
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = currentTime - lastTime;
    double deltaTime = elapsed.count();
    lastTime = currentTime;

    game.Update(deltaTime);
    game.DisplayOutput();
    game.HandleInput();
  }
  system("pause");
}

void Engine::ShowAnalytics() {
  system("cls");
  std::cout << "Total Games Played (All Types): "
            << statsManager.GetGamesPlayedCount() << std::endl;

  for (int i = 0; i < 5; i++) {
    std::cout << "\nGame: " << statsManager.GetGameName(i) << std::endl;
    std::cout << "  High Score:    " << statsManager.GetBestScore(i)
              << std::endl;
    std::cout << "  Average Score: " << statsManager.GetAverageScore(i)
              << std::endl;
    std::cout << "  Times Played:  "
              << statsManager.GetGameSpecificPlayCount(i) << std::endl;
  }
  system("pause");
}

void Engine::Run() {
  bool appRunning = true;
  while (appRunning) {
    system("cls");
    std::cout << "1. Play Game" << std::endl;
    std::cout << "2. View Analytics" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
      StartGameSession();
      break;
    case 2:
      ShowAnalytics();
      break;
    case 3:
      appRunning = false;
      std::cout << "Goodbye!" << std::endl;
      break;
    default:
      std::cout << "Invalid choice. Try again." << std::endl;
      break;
    }
  }
}
