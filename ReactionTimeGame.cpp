#include "ReactionTimeGame.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

ReactionTimeGame::ReactionTimeGame(std::string difficulty, StatisticsManager* stats, SoundManager* soundMgr)
    : BaseGame(difficulty, 60.0, stats, 2, soundMgr),  // 60 second time limit, game index 2
      targetActive(false),
      spawnTimer(0.0f),
      targetLifetime(0.0f),
      targetsClicked(0),
      targetsMissed(0),
      clickTime(0.0f),
      spawnMinX(100.0f),
      spawnMaxX(500.0f),
      spawnMinY(200.0f),
      spawnMaxY(800.0f)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    
    if (difficulty == "Easy") {
        targetRadius = 50.0f;
        nextSpawnDelay = 2.5f;
        targetMaxLifetime = 2.5f;
    } else if (difficulty == "Medium") {
        targetRadius = 40.0f;
        nextSpawnDelay = 2.0f;
        targetMaxLifetime = 2.0f;
    } else if (difficulty == "Hard") {
        targetRadius = 30.0f;
        nextSpawnDelay = 1.5f;
        targetMaxLifetime = 1.5f;
    } else {
        targetRadius = 40.0f;
        nextSpawnDelay = 2.0f;
        targetMaxLifetime = 2.0f;
    }
    
    StartTimer();
}

float ReactionTimeGame::getRandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void ReactionTimeGame::SetSpawnBounds(float minX, float maxX, float minY, float maxY) {
    spawnMinX = minX;
    spawnMaxX = maxX;
    spawnMinY = minY;
    spawnMaxY = maxY;
}

void ReactionTimeGame::generateNewTarget() {
    float margin = targetRadius + 20.0f;
    targetPosition.x = getRandomFloat(spawnMinX + margin, spawnMaxX - margin);
    targetPosition.y = getRandomFloat(spawnMinY + margin, spawnMaxY - margin);
    
    targetActive = true;
    targetLifetime = 0.0f;
    clickTime = 0.0f;
}

void ReactionTimeGame::Update(double deltaTime) {
    if (!IsGameActive()) return;
    
    UpdateTimer(deltaTime);
    
    if (targetActive) {
        targetLifetime += static_cast<float>(deltaTime);
        
        if (targetLifetime >= targetMaxLifetime) {
            targetActive = false;
            targetsMissed++;
            AddScore(-20);  
            spawnTimer = 0.0f;
            nextSpawnDelay = getRandomFloat(1.5f, 2.5f);
        }
    } else {
        spawnTimer += static_cast<float>(deltaTime);
        
        if (spawnTimer >= nextSpawnDelay) {
            generateNewTarget();
        }
    }
}

bool ReactionTimeGame::CheckClick(float mouseX, float mouseY, float& reactionTime) {
    if (!targetActive) return false;
    
    float dx = mouseX - targetPosition.x;
    float dy = mouseY - targetPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    if (distance <= targetRadius) {
        targetActive = false;
        targetsClicked++;
        
        reactionTime = targetLifetime;
        int baseScore = 100;
        
        if (reactionTime < 0.5f) {
            int bonus = static_cast<int>((0.5f - reactionTime) * 100);
            AddScore(baseScore + bonus);
        } else {
            AddScore(baseScore);
        }
        
        spawnTimer = 0.0f;
        nextSpawnDelay = getRandomFloat(1.5f, 2.5f);
        
        return true;
    }
    
    return false;
}

void ReactionTimeGame::DisplayOutput() {
    std::cout << "Score: " << currentScore << std::endl;
    std::cout << "Time: " << GameTimer << "/" << TimeLimit << std::endl;
    std::cout << "Targets Clicked: " << targetsClicked << std::endl;
    std::cout << "Targets Missed: " << targetsMissed << std::endl;
}

void ReactionTimeGame::HandleInput() {
}
