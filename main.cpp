#include <_timeval.h>
#include <ctime>
#include <exception>
#include <iomanip>
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
//--------------------------------//

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
        InternalGameStatistics(nullptr) {}

  BaseGame(int currentScore, double GameTimer, double TimeLimit,
           double ScoreMultiplier, bool IsPaused, bool IsGameOver,
           bool TimerActive, StatisticsManager *statsManager)
      : currentScore(currentScore), GameTimer(GameTimer), TimeLimit(TimeLimit),
        ScoreMultiplier(ScoreMultiplier), IsPaused(IsPaused),
        IsGameOver(IsGameOver), TimerActive(TimerActive),
        InternalGameStatistics(statsManager) {}

  BaseGame(std::string difficulty, double TimeLimit,
           StatisticsManager *statsManager)
      : currentScore(0), GameTimer(0.0), TimeLimit(TimeLimit), IsPaused(false),
        IsGameOver(false), TimerActive(false),
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

  void AddScore(int Points, double ScoreMultiplier) {

    currentScore = Points * ScoreMultiplier;
  }

  void SubtractPoint(int Points) {
    currentScore = currentScore - Points;

    if (currentScore < 0) {

      std::cout << "The Score is already Zero" << std::endl;
    }
  }

  int GetCurrentScore() { return currentScore; }

  void ResestScore() { currentScore = 0; }

  void StartTimer() { TimerActive = true; }

  void UpdateTimer(double ChangeInTime) {}

  void PauseTimer() { TimerActive = false; }

  void ResumeTimer() { TimerActive = true; }

  double GetElapsedTimer() { return GameTimer; }

  double GetRemainingTime() { return TimeLimit - GameTimer; }

  bool isTimeUp() {}
  void PauseGame() { IsPaused = true; }
  void ResumeGame() {

    IsPaused = false;

    BaseGame::ResumeGame();

    std::cout << "Game Reusmed" << std::endl;
  }

  void TogglePause() {

    if (IsPaused == true) {
      BaseGame::ResumeGame();

    }

    else {

      BaseGame::PauseGame();
    }
  }

  void SetDifficulty(std::string GivenDiffculty) {
    difficultyLevel = GivenDiffculty;
    if (GivenDiffculty == "Easy") {

      ScoreMultiplier = 1.0;

    } else if (GivenDiffculty == "Medium") {

      ScoreMultiplier = 1.5;

    }

    else if (GivenDiffculty == "Hard") {

      ScoreMultiplier = 2.0;
    }
  }

  std::string GetDifficulty() { return difficultyLevel; }

  double GetScoreMultipler() { return ScoreMultiplier; }

  void EndGame() {

    IsGameOver = IsGameOver = true;

    TimerActive = false;
    // will save score once i created the state manager
    // will go back to reuslts scree.
  }

  void RestartGame() {

    BaseGame::ResestScore();
    BaseGame::ResumeTimer();
    BaseGame::IsPaused = false;
    BaseGame::IsGameOver = false;
  }

  virtual void HanldeInput(std::string Event_Name) {
    // this will be an sfml object inthe input
  }

  virtual void Update(double TimeChange) {}

  virtual void displayOutput() {

    // this will become an render function
    // when we use sfml
  }
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
