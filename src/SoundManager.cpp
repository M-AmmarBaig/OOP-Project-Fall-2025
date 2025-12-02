#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager() : buttonClickSound(buttonClickBuffer), scoreSound(scoreBuffer), penaltySound(penaltyBuffer) {
}

SoundManager::~SoundManager() {
}

bool SoundManager::loadButtonClickSound(const std::string& filename) {
    if (!buttonClickBuffer.loadFromFile(filename)) {
        std::cerr << "Error: Could not load button click sound: " << filename << std::endl;
        return false;
    }
    buttonClickSound.setVolume(25.0f);
    return true;
}

void SoundManager::playButtonClick() {
    if (buttonClickSound.getStatus() != sf::SoundSource::Status::Playing) {
        buttonClickSound.play();
    }
}

bool SoundManager::loadScoreSound(const std::string& filename) {
    if (!scoreBuffer.loadFromFile(filename)) {
        std::cerr << "Error: Could not load score sound: " << filename << std::endl;
        return false;
    }
    scoreSound.setVolume(30.0f);
    return true;
}

void SoundManager::playScoreSound() {
    scoreSound.play();
}

bool SoundManager::loadPenaltySound(const std::string& filename) {
    if (!penaltyBuffer.loadFromFile(filename)) {
        std::cerr << "Error: Could not load penalty sound: " << filename << std::endl;
        return false;
    }
    penaltySound.setVolume(28.0f);
    return true;
}

void SoundManager::playPenaltySound() {
    penaltySound.play();
}

bool SoundManager::loadBackgroundMusic(const std::string& filename) {
    if (!backgroundMusic.openFromFile(filename)) {
        std::cerr << "Error: Could not load background music: " << filename << std::endl;
        return false;
    }
    backgroundMusic.setLooping(true);
    backgroundMusic.setVolume(10.0f);
    return true;
}

void SoundManager::playBackgroundMusic() {
    if (backgroundMusic.getStatus() != sf::SoundSource::Status::Playing) {
        backgroundMusic.play();
    }
}


