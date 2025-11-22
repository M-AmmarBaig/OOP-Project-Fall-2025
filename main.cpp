#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <vector>

// Data structure to hold stats for a single game
class GameStat {
public:
  std::string gameName;
  int scores[100];
  int highScore;
  int playCount;
  int scoreCount;
};

// --- Screen Placeholders (Future GUI use) ---
class BaseScreen {};
class MainMenu : public BaseScreen {};
class GameSelect : public BaseScreen {};
class SetDiffScreen : public BaseScreen {};
class AnalyticsScreen : public BaseScreen {};
class GameAnalyticsScreen : public BaseScreen {};
class PauseScreen : public BaseScreen {};
class ResultScreen : public BaseScreen {};

// --- Statistics Manager ---
class StatisticsManager {
private:
  GameStat allGames[5];
  std::string SaveFileName;
  int totalGamesPlayed;

public:
  StatisticsManager(std::string saveFileName = "game_stats.txt")
      : SaveFileName(saveFileName), totalGamesPlayed(0) {

    // Initialize all 5 games
    allGames[0].gameName = "MemoryMatch";
    allGames[0].scoreCount = 0;
    allGames[0].highScore = 0;
    allGames[0].playCount = 0;

    allGames[1].gameName = "MathSpeed";
    allGames[1].scoreCount = 0;
    allGames[1].highScore = 0;
    allGames[1].playCount = 0;

    allGames[2].gameName = "ReactionTime";
    allGames[2].scoreCount = 0;
    allGames[2].highScore = 0;
    allGames[2].playCount = 0;

    allGames[3].gameName = "CardsMatching";
    allGames[3].scoreCount = 0;
    allGames[3].highScore = 0;
    allGames[3].playCount = 0;

    allGames[4].gameName = "StroopTest";
    allGames[4].scoreCount = 0;
    allGames[4].highScore = 0;
    allGames[4].playCount = 0;
  }

  bool ReadFromFile() {
    std::fstream Input(SaveFileName);
    if (!Input.is_open()) {
      std::cout << "The file is not opened properly (First run?)" << std::endl;
      return false;
    } else {
      for (int i = 0; i < 5; i++) {
        std::getline(Input, allGames[i].gameName);
        Input >> allGames[i].scoreCount;
        Input >> allGames[i].highScore;
        Input >> allGames[i].playCount;
        for (int j = 0; j < allGames[i].scoreCount; j++) {
          Input >> allGames[i].scores[j];
        }
        Input.ignore(); // Consume the newline after reading scores
      }
    }
    Input.close();
    return true;
  }

  bool SaveToFile() {
    std::ofstream outputFile(SaveFileName);
    if (!outputFile.is_open()) {
      std::cout << "Error: Could not open file for writing." << std::endl;
      return false;
    } else {
      for (int i = 0; i < 5; i++) {
        outputFile << allGames[i].gameName << "\n";
        outputFile << allGames[i].scoreCount << "\n";
        outputFile << allGames[i].highScore << "\n";
        outputFile << allGames[i].playCount << "\n";

        for (int j = 0; j < allGames[i].scoreCount; j++) {
          outputFile << allGames[i].scores[j] << " ";
        }
        outputFile << "\n";
      }
    }
    outputFile.close();
    return true;
  }

  void SetScore(int GameIndex, int Score) {};

  void SaveScore(int gameindex, int score) {
    if (gameindex > 4 || gameindex < 0) {
      std::cout << "The game index is invalid." << std::endl;
      return;
    } else if (allGames[gameindex].scoreCount >= 100) {
      std::cout << "Score history is full." << std::endl;
    } else {
      int temp_score_count = allGames[gameindex].scoreCount;
      allGames[gameindex].scores[temp_score_count] = score;
      allGames[gameindex].scoreCount++;
    }

    if (score > allGames[gameindex].highScore) {
      allGames[gameindex].highScore = score;
    }
    allGames[gameindex].playCount++;
    SaveToFile();
  }

  double GetBestScore(int GameIndex) {
    if (GameIndex < 0 || GameIndex > 4)
      return 0;
    return allGames[GameIndex].highScore;
  }

  int GetScoreHistory(int GameIndex, int outputArray[]) {
    if (GameIndex < 0 || GameIndex > 4)
      return 0;
    int count = allGames[GameIndex].scoreCount;
    for (int i = 0; i < count; i++) {
      outputArray[i] = allGames[GameIndex].scores[i];
    }
    return count;
  }

  int GetGamesPlayedCount() {
    int total = 0;
    for (int i = 0; i < 5; i++) {
      total += allGames[i].playCount;
    }
    return total;
  }

  // New Helper: Get play count for a specific game
  int GetGameSpecificPlayCount(int GameIndex) {

    return allGames[GameIndex].playCount;
  }

  std::string GetGameName(int GameIndex) {
    return allGames[GameIndex].gameName;
  }

  double GetAverageScore(int GameIndex) {
    if (allGames[GameIndex].scoreCount == 0)
      return 0.0;

    double scoresum = 0;
    for (int i = 0; i < allGames[GameIndex].scoreCount; i++) {
      scoresum += allGames[GameIndex].scores[i];
    }
    return scoresum / allGames[GameIndex].scoreCount;
  }

  void ResetStats(int GameIndex) {

    allGames[GameIndex].scoreCount = 0;
    allGames[GameIndex].highScore = 0;
    allGames[GameIndex].playCount = 0;
    SaveToFile();
  }

  double GetLastBestScore(int GameIndex) {

    if (allGames[GameIndex].scoreCount == 0)
      return 0;
    int lastIndex = allGames[GameIndex].scoreCount - 1;
    return allGames[GameIndex].scores[lastIndex];
  }
};

// --- Base Game Class ---
class BaseGame {
private:
  int currentScore;
  double GameTimer;
  double TimeLimit;
  double ScoreMultiplier;
  bool IsPaused;
  bool IsGameOver;
  bool TimerActive;
  std::string difficultyLevel;

public:
  StatisticsManager *InternalGameStatistics;

  BaseGame()
      : currentScore(0), GameTimer(0.0), TimeLimit(0.0), ScoreMultiplier(1.0),
        IsPaused(false), IsGameOver(false), TimerActive(false),
        difficultyLevel("Easy"), InternalGameStatistics(nullptr) {}

  BaseGame(std::string difficulty, double TimeLimit,
           StatisticsManager *statsManager)
      : currentScore(0), GameTimer(0.0), TimeLimit(TimeLimit), IsPaused(false),
        IsGameOver(false), TimerActive(false), difficultyLevel(difficulty),
        InternalGameStatistics(statsManager) {

    SetDifficulty(difficulty);
  }

  void AddScore(int Points) { currentScore += Points; }

  void ResetScore() { currentScore = 0; }

  void StartTimer() {
    GameTimer = 0.0;
    TimerActive = true;
  }

  void UpdateTimer(double ChangeInTime) {
    if (TimerActive && !IsPaused) {
      GameTimer += ChangeInTime;
      if (IsTimeUp()) {
        EndGame();
      }
    }
  }

  bool IsTimeUp() {
    if (TimeLimit <= 0.0)
      return false;
    return GameTimer >= TimeLimit;
  }

  void SetDifficulty(std::string GivenDifficulty) {
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

  std::string GetDifficulty() { return difficultyLevel; }

  void EndGame() {
    IsGameOver = true;
    TimerActive = false;
    std::cout << "Game Over! Final Score: " << currentScore << std::endl;
    if (InternalGameStatistics != nullptr) {
      // abhi memeory match me sirf score store kerha hu cuz baki ke games
      // create  nhi kie hye hai
      InternalGameStatistics->SaveScore(0, currentScore);
    }
  }

  bool IsGameActive() { return !IsPaused && !IsGameOver; }

  virtual void HandleInput() = 0;
  virtual void Update(double TimeChange) { UpdateTimer(TimeChange); }
  virtual void DisplayOutput() = 0;
  virtual ~BaseGame() {}
};

// --- Memory Match Game ---
class MemoryMatch : public BaseGame {
private:
  std::vector<int> sequence;
  bool isShowingPattern;
  double messageTimer;

  void AddToSequence() {
    int nextNum = (rand() % 4) + 1;
    sequence.push_back(nextNum);
  }

public:
  MemoryMatch(std::string difficulty, StatisticsManager *stats)
      : BaseGame(difficulty, 0.0, stats) {
    isShowingPattern = true;
    messageTimer = 0.0;
    AddToSequence();
    AddToSequence();
    AddToSequence();
  }

  void Update(double deltaTime) override { BaseGame::Update(deltaTime); };

  void DisplayOutput() override {
    if (isShowingPattern == true) {
      system("cls");
      std::cout << "Memorize This Sequence..." << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));

      for (int i = 0; i < sequence.size(); i++) {
        system("cls");
        std::cout << "\n\n   " << sequence[i] << "   \n\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        system("cls");
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }
      isShowingPattern = false;
    } else {
      std::cout << "Welcome To Memory Match" << std::endl;
      std::cout << "Current difficulty: " << GetDifficulty() << std::endl;
      std::cout << "YOUR TURN! Type the numbers..." << std::endl;
    }
  }

  void HandleInput() override {
    if (isShowingPattern == true) {
      return;
    } else {
      for (int i = 0; i < sequence.size(); i++) {
        int user_guess = 0;
        std::cin >> user_guess;

        if (std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(10000, '\n');
          std::cout << "Invalid Input" << std::endl;
          EndGame();
          return;
        }

        if (user_guess == sequence[i]) {
          std::cout << "Matched" << std::endl;
        } else {
          std::cout << "Game Over!" << std::endl;
          EndGame();
          return;
        }
      }
      AddScore(100);
      AddToSequence();
      isShowingPattern = true;
    }
  };
};

class MathSpeedGame : public BaseGame {
  void HandleInput() override {}
  void DisplayOutput() override {}
};
class ReactionTime : public BaseGame {
  void HandleInput() override {}
  void DisplayOutput() override {}
};
class CardMatchingGame : public BaseGame {
  void HandleInput() override {}
  void DisplayOutput() override {}
};
class StroopTestGame : public BaseGame {
  void HandleInput() override {}
  void DisplayOutput() override {}
};

// --- Engine ---
class Engine {
private:
  StatisticsManager statsManager;

  void StartGameSession() {
    std::cout << "Select Difficulty (Easy, Medium, Hard): ";
    std::string diff;
    std::cin >> diff;

    // Abhi MemoryMatch ke lie sirf hard code kia hua hai baad me change hoga
    // yee!
    MemoryMatch game(diff, &statsManager);
    game.StartTimer();

    while (game.IsGameActive()) {
      game.DisplayOutput();
      game.HandleInput();
      game.Update(0.0);
    }
    system("pause");
  }

  void ShowAnalytics() {
    system("cls");
    std::cout << "Total Games Played (All Types): "
              << statsManager.GetGamesPlayedCount() << std::endl;
    std::cout << "-----------------------------" << std::endl;

    for (int i = 0; i < 5; i++) {
      std::cout << "Game: " << statsManager.GetGameName(i) << std::endl;
      std::cout << "  High Score:    " << statsManager.GetBestScore(i)
                << std::endl;
      std::cout << "  Average Score: " << statsManager.GetAverageScore(i)
                << std::endl;
      std::cout << "  Times Played:  "
                << statsManager.GetGameSpecificPlayCount(i) << std::endl;
    }
    system("pause");
  }

public:
  Engine() : statsManager("game_data.txt") { statsManager.ReadFromFile(); }

  void Run() {
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
};

int main() {
  srand(time(0));
  Engine engine;
  engine.Run();
  return 0;
}
