#include <_timeval.h>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

class GameStat {

public:
  std::string gameName;
  int scores[100];
  int highScore;
  int playCount;
  int scoreCount;
};

class BaseScreen {
  // This is a like default template or base constructor type
  // for child classes. It doesn't do anything on its own but rather defines
  // others.
};

//-------------------------------------- Screens Inherent From BaseScreen
//--------------------------//

class MainMenu : public BaseScreen {
  // This class will inherit from the above base screen
  // because the upper BaseScreen class will have multiple defined constructors.
};

class GameSelect : public BaseScreen {
  // Same here, will come back here to put the attributes and properties
};

class SetDiffScreen : public BaseScreen {
  // This class will help us to set the difficulty from.
};

class AnalyticsScreen : public BaseScreen {};

class GameAnalyticsScreen : public BaseScreen {
  // This will show individual game states not the general overall states.
};

class PauseScreen : public BaseScreen {};

class ResultScreen : public BaseScreen {};

//--------------------- Main Game Logic Nut Bolts

class StatisticsManager {

private:
  GameStat allGames[5];

  std::string SaveFileName;
  int totalGamesPlayed;

public:
  StatisticsManager(std::string saveFileName = "game_stats.txt")
      : SaveFileName(saveFileName), totalGamesPlayed(0) {

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

      std::cout << "The file is not opened properly" << std::endl;

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

        Input.ignore();
      }
    }
    Input.close();

    return true;
  }

  bool SaveToFile() {

    std::ofstream outputFile(SaveFileName);

    std::fstream Input(SaveFileName);

    if (!outputFile.is_open()) {
      std::cout << "Error: Could not open file for writing." << std::endl;
      return false;
    } else {

      for (int i = 0; i < 5; i++) {

        std::string GameName = allGames[i].gameName;
        int scoreCount = allGames[i].scoreCount;
        int highScore = allGames[i].highScore;
        int playCount = allGames[i].playCount;

        outputFile << GameName << "\n";
        outputFile << scoreCount << "\n";
        outputFile << highScore << "\n";
        outputFile << playCount << "\n";

        for (int j = 0; j < scoreCount; j++) {
          outputFile << allGames[i].scores[j] << " ";
        }

        outputFile << "\n";
      }
    }
  }

  void SetScore(int GameIndex, int Score) {

  };

  void SaveScore(int gameindex, int score) {

    if (gameindex > 4 || gameindex < 0) {
      std::cout << "the game index is invalid please enter teh right index"
                << std::endl;
      return;
    }

    else if (allGames[gameindex].scoreCount >= 100) {
      std::cout << "the score count is full cannot add more scores"
                << std::endl;
    }

    else {
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
  double GetBestScore(int GameIndex) { return allGames[GameIndex].highScore; }

  int GetScoreHistory(int GameIndex, int outputArray[]) {

    int count = allGames[GameIndex].scoreCount;

    for (int i = 0; i < count; i++) {
      outputArray[i] = allGames[GameIndex].scores[i];
    }

    return count;
  }

  int GetGamesPlayedCount() {

    int allgames = 0;

    for (int i = 0; i < 4; i++) {

      allgames = +allGames[i].playCount;
    }
    return allgames;
  }

  double GetAverageScore(int GameIndex) {
    double scoresum = 0;

    for (int i = 0; i < allGames[GameIndex].scoreCount; i++) {

      scoresum += allGames[GameIndex].scores[i];
    }
    double average = scoresum / allGames[GameIndex].scoreCount;

    return average;
  }
  void ResestStats(int GameIndex) {

    allGames[GameIndex].scoreCount = 0;
    allGames[GameIndex].highScore = 0;
    allGames[GameIndex].playCount = 0;
    SaveToFile();
  }

  double GetLastBestScore(int GameIndex) {

    int lastIndex = allGames[GameIndex].scoreCount - 1;
    return allGames[GameIndex].scores[lastIndex];
  }
};

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

  BaseGame(int currentScore, double GameTimer, double TimeLimit,
           double ScoreMultiplier, bool IsPaused, bool IsGameOver,
           bool TimerActive, StatisticsManager *statsManager)
      : currentScore(currentScore), GameTimer(GameTimer), TimeLimit(TimeLimit),
        ScoreMultiplier(ScoreMultiplier), IsPaused(IsPaused),
        IsGameOver(IsGameOver), TimerActive(TimerActive),
        difficultyLevel("Easy"), InternalGameStatistics(statsManager) {}

  BaseGame(std::string difficulty, double TimeLimit,
           StatisticsManager *statsManager)
      : currentScore(0), GameTimer(0.0), TimeLimit(TimeLimit), IsPaused(false),
        IsGameOver(false), TimerActive(false), difficultyLevel(difficulty),
        InternalGameStatistics(statsManager) {
    if (difficulty == "Easy") {
      ScoreMultiplier = 1.0;
    } else if (difficulty == "Medium") {
      ScoreMultiplier = 1.5;
    } else if (difficulty == "Hard") {
      ScoreMultiplier = 2.0;
    } else {
      ScoreMultiplier = 1.0;
    }
  }

  void AddScore(int Points) { currentScore += Points; }

  void AddScore(int Points, double CustomMultiplier) {
    currentScore += (Points * CustomMultiplier);
  }

  void SubtractPoint(int Points) {
    if (currentScore - Points < 0) {
      currentScore = 0;
      std::cout << "Score cannot go below zero. Setting score to 0."
                << std::endl;
    } else {
      currentScore -= Points;
    }
  }

  int GetCurrentScore() { return currentScore; }

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

  void PauseTimer() { TimerActive = false; }

  void ResumeTimer() { TimerActive = true; }

  double GetElapsedTime() { return GameTimer; }

  double GetRemainingTime() {
    double remaining = TimeLimit - GameTimer;
    return (remaining > 0.0) ? remaining : 0.0;
  }

  bool IsTimeUp() {
    if (TimeLimit <= 0.0) {
      return false;
    }
    return GameTimer >= TimeLimit;
  }

  void SetTimeLimit(double newLimit) { TimeLimit = newLimit; }

  void PauseGame() {
    IsPaused = true;
    PauseTimer();
    std::cout << "Game Paused" << std::endl;
  }

  void ResumeGame() {
    IsPaused = false;
    ResumeTimer();
    std::cout << "Game Resumed" << std::endl;
  }

  void TogglePause() {
    if (IsPaused == false) {
      ResumeGame();
    } else {
      PauseGame();
    }
  }

  bool CheckIfPaused() { return IsPaused; }

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

  double GetScoreMultiplier() { return ScoreMultiplier; }

  void EndGame() {
    IsGameOver = true;
    TimerActive = false;

    std::cout << "Game Over! Final Score: " << currentScore << std::endl;

    if (InternalGameStatistics != nullptr) {
      // InternalGameStatistics->SaveScore(gameName, currentScore);
    }

    // TODO: Switch to ResultsScreen via ScreenManager
  }

  void RestartGame() {
    ResetScore();
    GameTimer = 0.0;
    IsPaused = false;
    IsGameOver = false;
    StartTimer();

    std::cout << "Game Restarted" << std::endl;
  }

  bool CheckIfGameOver() { return IsGameOver; }

  bool IsGameActive() { return !IsPaused && !IsGameOver; }

  virtual void HandleInput(std::string Event_Name) = 0;

  virtual void Update(double TimeChange) { UpdateTimer(TimeChange); }

  virtual void DisplayOutput() = 0;

  virtual ~BaseGame() {}
};

class Button {
  // This will draw different buttons on the screen.
  // I might add methods for button pressed and actions etc
  // There might be child instances of this class like pause button, menu
  // button etc
};

class MemoryMatch : public BaseGame {
private:
  std::string Sequence[100];
  std::string PlayerInput[100];
  GameStateManger GameState;
  Button GameButton;

public:
  MemoryMatch(std::string Sequence, std::string PlayerInput,
              GameStateManger GameState, Button GameButton)
      : BaseGame(), Sequence(Sequence), PlayerInput(PlayerInput),
        GameState(GameState), GameButton(GameButton) {}

  void GetCurrentSequence() {
    // Implementation
  }

  void ShowSequence() {
    // Implementation
  }

  std::string ReadUserInput() {
    // This function will take an array input
  }
};

class MathSpeedGame : public BaseGame {};

class ReactionTime : public BaseGame {};

class CardMatchingGame : public BaseGame {};

class StroopTestGame : public BaseGame {
  // Might remove this later
};

//----------------------------- Small Helper Classes
//-----------------------------//

class StatisticsManger {};

class AssestManger {
  // This class is for grabbing graphics, fonts and other material for
  // display.
};

class Engine {
  // This class will handle all the operations.
  // 1. Like creating game screens
  // 2. Manages main SFML windows when we implement the UI.
  // 3. Will directly communicate with the screen manager class.
  // 4. Will manage global events like click and updates.
  // When this class will be triggered it will only hold a single instance of
  // screen/statistics.
};
