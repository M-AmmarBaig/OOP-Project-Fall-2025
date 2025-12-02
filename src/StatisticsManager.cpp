#include "StatisticsManager.h"
#include <fstream>
#include <iostream>
#include <limits>

StatisticsManager::StatisticsManager(std::string saveFileName)
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

  allGames[3].gameName = "StroopTest";
  allGames[3].scoreCount = 0;
  allGames[3].highScore = 0;
  allGames[3].playCount = 0;
//use nhi kerha abhi since we are not doing a 5th game 
  allGames[4].gameName = "";
  allGames[4].scoreCount = 0;
  allGames[4].highScore = 0;
  allGames[4].playCount = 0;
}

bool StatisticsManager::ReadFromFile() {
  std::fstream Input(SaveFileName);
  if (!Input.is_open()) {
    std::cout << "The file is not opened properly (First run?)" << std::endl;
    return false;
  } else {
    for (int i = 0; i < 5; i++) {
      std::string tempName;
      std::getline(Input, tempName);
      
      Input >> allGames[i].scoreCount;
      Input >> allGames[i].highScore;
      Input >> allGames[i].playCount;
      for (int j = 0; j < allGames[i].scoreCount; j++) {
        Input >> allGames[i].scores[j];
      }
      Input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  Input.close();
  return true;
}

bool StatisticsManager::SaveToFile() {
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

void StatisticsManager::SaveScore(int gameindex, int score) {
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

double StatisticsManager::GetBestScore(int GameIndex) {
  if (GameIndex < 0 || GameIndex > 4)
    return 0;
  return allGames[GameIndex].highScore;
}

int StatisticsManager::GetGamesPlayedCount() {
  int total = 0;
  for (int i = 0; i < 5; i++) {
    total += allGames[i].playCount;
  }
  return total;
}

int StatisticsManager::GetGameSpecificPlayCount(int GameIndex) {
  return allGames[GameIndex].playCount;
}

std::string StatisticsManager::GetGameName(int GameIndex) {
  return allGames[GameIndex].gameName;
}

double StatisticsManager::GetAverageScore(int GameIndex) {
  if (allGames[GameIndex].scoreCount == 0)
    return 0.0;

  double scoresum = 0;
  for (int i = 0; i < allGames[GameIndex].scoreCount; i++) {
    scoresum += allGames[GameIndex].scores[i];
  }
  return scoresum / allGames[GameIndex].scoreCount;
}
