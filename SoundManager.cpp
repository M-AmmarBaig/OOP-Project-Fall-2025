#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager() : buttonClickSound(buttonClickBuffer) {
}

SoundManager::~SoundManager() {
}

bool SoundManager::loadButtonClickSound(const std::string& filename) {
    if (!buttonClickBuffer.loadFromFile(filename)) {
        std::cerr << "Error: Could not load button click sound: " << filename << std::endl;
        return false;
    }
    buttonClickSound.setVolume(50.0f);
    return true;
}

void SoundManager::playButtonClick() {
    if (buttonClickSound.getStatus() != sf::SoundSource::Status::Playing) {
        buttonClickSound.play();
    }
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

void SoundManager::pauseBackgroundMusic() {
    backgroundMusic.pause();
}

void SoundManager::stopBackgroundMusic() {
    backgroundMusic.stop();
}

void SoundManager::setMusicVolume(float volume) {
    backgroundMusic.setVolume(volume);
}
