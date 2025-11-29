#ifndef REACTIONTIMEGAME_H
#define REACTIONTIMEGAME_H

#include "BaseGame.h"
#include <SFML/System/Vector2.hpp>

class ReactionTimeGame : public BaseGame {
private:
    sf::Vector2f targetPosition;
    float targetRadius;
    bool targetActive;
    float spawnTimer;
    float nextSpawnDelay;
    float targetLifetime;
    float targetMaxLifetime;
    float clickTime;
    int targetsClicked;
    int targetsMissed;
    
    float spawnMinX;
    float spawnMaxX;
    float spawnMinY;
    float spawnMaxY;

    void generateNewTarget();
    float getRandomFloat(float min, float max);

public:
    ReactionTimeGame(std::string difficulty, StatisticsManager* stats);
    
    void SetSpawnBounds(float minX, float maxX, float minY, float maxY);
    
    void Update(double deltaTime) override;
    void DisplayOutput() override;
    void HandleInput() override;
    
    bool CheckClick(float mouseX, float mouseY, float& reactionTime);
    sf::Vector2f GetTargetPosition() const { return targetPosition; }
    float GetTargetRadius() const { return targetRadius; }
    bool IsTargetActive() const { return targetActive; }
    int GetTargetsClicked() const { return targetsClicked; }
    int GetTargetsMissed() const { return targetsMissed; }
};

#endif
