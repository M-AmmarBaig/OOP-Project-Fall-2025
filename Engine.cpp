#include "Engine.h"
#include "MainMenuScreen.h"

#include <iostream>

Engine::Engine() : statsManager("game_data.txt") {
    window.create(sf::VideoMode({540, 960}), "Brain Games Engine");
    window.setFramerateLimit(60);

    if (!mainFont.openFromFile("JetBrainsMonoNerdFont-Bold.ttf")) {
        std::cerr << "CRITICAL ERROR: Could not load arial.ttf" << std::endl;
    }

    if (!soundManager.loadButtonClickSound("button_click.mp3")) {
        std::cerr << "WARNING: Could not load button click sound" << std::endl;
    }

    statsManager.ReadFromFile();

    currentScreen = new MainMenuScreen(this);
}

Engine::~Engine() {
    if (currentScreen != nullptr) {
        delete currentScreen;
    }
}

void Engine::switchScreen(BaseScreen* newScreen) {
    if (currentScreen != nullptr) {
        delete currentScreen;
    }
    currentScreen = newScreen;
}

void Engine::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (currentScreen != nullptr) {
                currentScreen->handleInput(*event, window);
            }
        }

        if (currentScreen != nullptr) {
            currentScreen->update(deltaTime);
        }

        window.clear(sf::Color(20, 30, 40));

        if (currentScreen != nullptr) {
            currentScreen->render(window);
        }

        window.display();
    }
}
