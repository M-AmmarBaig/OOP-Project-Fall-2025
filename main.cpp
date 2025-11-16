#include <_timeval.h>
#include <ctime>
#include <exception>
#include <iostream>
#include <random>
#include <shared_mutex>
#include <stdexcept>
#include <string>

class GameStateManger {
  // 1. This will hold the reference to the current screen which is shown.
  // 2. Will manage the switching between different screens.
  // 3. Will handle the multiple states of the screens like pause/play etc.
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

class StatisticsManager {};

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
  // There might be child instances of this class like pause button, menu button
  // etc
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
  // This class is for grabbing graphics, fonts and other material for display.
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
