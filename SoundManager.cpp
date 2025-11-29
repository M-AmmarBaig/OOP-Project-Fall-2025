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
