# 🧠 Brain Games

A collection of interactive brain training games built with C++ and SFML. Challenge your memory, math skills, reaction time, and cognitive abilities!

**Table of Contents:**
- [Features](#features)
- [Games Included](#games-included)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Compilation](#compilation)
- [Running the Game](#running-the-game)
- [Game Controls](#game-controls)
- [Project Structure](#project-structure)

**Features:**
- **4 Different Brain Training Games** - Test various cognitive abilities
- **Statistics Tracking** - Track your high scores, averages, and play counts
- **Analytics Dashboard** - View detailed performance metrics for each game
- **Sound Effects** - Immersive audio feedback (background music, button clicks, score sounds)
- **Modern GUI** - Clean SFML-based graphical interface
- **Persistent Data** - Your game statistics are saved automatically

**Games Included:**
###1. **Memory Match** 
Test your memory by memorizing and repeating sequences of numbers. Sequences get longer as you progress!

### 2. **Math Speed** 
Solve math problems as quickly as possible. Race against the clock to answer addition, subtraction, and multiplication questions.

### 3. **Reaction Time** 
Click on targets as quickly as possible. Test your reflexes and hand-eye coordination.

### 4. **Stroop Test** 
Identify the color of text while ignoring the word itself. A classic cognitive interference test.

## **Prerequisites:**
Before compiling and running Brain Games, ensure you have the following installed:

### **Required Software:**
- **C++ Compiler** with C++20 support
  - Windows: MinGW-w64 (GCC) or MSVC
  
- **SFML 3.0.2** (Simple and Fast Multimedia Library)
  - Download from: [SFML Official Website](https://www.sfml-dev.org/download.php)


##  **Installation Steps:**
### Step 1: Clone or Download the Project

```bash
git clone https://github.com/M-AmmarBaig/OOP-Project-Fall-2025.git
cd OOP-Project-Fall-2025
```

*Or download the ZIP file and extract it to your desired location.*

### Step 2: Install SFML

#### Windows (MinGW)
1. Download SFML 3.0.2 for MinGW from the [SFML downloads page](https://www.sfml-dev.org/download.php)
2. Extract SFML to `C:\SFML-3.0.2\` (or your preferred location)
3. Ensure the SFML `bin` folder is in your system PATH or copy DLLs to the project directory

### Step 3: Verify Required Assets

Ensure the following directory structure exists with all asset files:
```
assets/
├── fonts/
│   └── JetBrainsMonoNerdFont-Bold.ttf
├── images/
│   ├── Main-Game-Menu.png
│   └── ARIAL.png
└── sounds/
    ├── background_music.mp3
    ├── button_click.mp3
    ├── score_sound.mp3
    └── penalty_sound.mp3
```

## Compilation

### Windows (MinGW with G++)

#### One-Line Compilation (Recommended)
```bash
g++ src/*.cpp -o BrainGames.exe -Iinclude -IC:\SFML-3.0.2\include -LC:\SFML-3.0.2\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++20
```

#### Compile Individual Source Files (Alternative)
```bash
g++ -c src/main.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/Engine.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/BaseGame.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/Button.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/SoundManager.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/StatisticsManager.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/MainMenuScreen.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/GameSelectScreen.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/AnalyticsMenuScreen.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/GameAnalyticsScreen.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/OverallAnalyticsScreen.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/MathSpeedGame.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/MathSpeedScreen.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/MemoryMatch.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/MemoryMatchScreen.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/ReactionTimeGame.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/ReactionTimeScreen.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/StroopTestGame.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
g++ -c src/StroopTestScreen.cpp -Iinclude -IC:\SFML-3.0.2\include -std=c++20
```

#### Link to Create Executable
```bash
g++ *.o -o BrainGames.exe -LC:\SFML-3.0.2\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++20
```

## **Running the Game:**
```bash
.\BrainGames.exe
```

##**Game Controls:**
### General Navigation
- **Mouse Click** - Select menu options and buttons
- **Mouse Hover** - Highlight buttons and interactive elements

### 1. Math Speed Game
- **Keyboard** - Type your answer and press Enter
- **Backspace** - Correct typing mistakes

### 2. Memory Match Game
- **Keyboard** - Type numbers from the sequence

### 3. Reaction Time Game
- **Mouse Click** - Click on targets as they appear

### 4. Stroop Test Game
- **Mouse Click** - Click the color button that matches the text color (not the word)


## **Project Structure:**
```
OOP-Project-Fall-2025/
├── src/                              # Source files (.cpp)
│   ├── main.cpp                      # Entry point
│   ├── Engine.cpp                    # Main game engine
│   ├── BaseGame.cpp                  # Base game class
│   ├── Button.cpp                    # GUI button component
│   ├── SoundManager.cpp              # Audio management
│   ├── StatisticsManager.cpp         # Game stats tracking
│   ├── MainMenuScreen.cpp            # Main menu screen
│   ├── GameSelectScreen.cpp          # Game selection screen
│   ├── AnalyticsMenuScreen.cpp       # Analytics menu screen
│   ├── GameAnalyticsScreen.cpp       # Individual game analytics
│   ├── OverallAnalyticsScreen.cpp    # Overall analytics screen
│   ├── MathSpeedGame.cpp             # Math game logic
│   ├── MathSpeedScreen.cpp           # Math game screen
│   ├── MemoryMatch.cpp               # Memory game logic
│   ├── MemoryMatchScreen.cpp         # Memory game screen
│   ├── ReactionTimeGame.cpp          # Reaction game logic
│   ├── ReactionTimeScreen.cpp        # Reaction game screen
│   ├── StroopTestGame.cpp            # Stroop game logic
│   └── StroopTestScreen.cpp          # Stroop game screen
│
├── include/                          # Header files (.h)
│   ├── Engine.h
│   ├── BaseGame.h
│   ├── BaseScreen.h
│   ├── Button.h
│   ├── SoundManager.h
│   ├── StatisticsManager.h
│   ├── GameStat.h
│   ├── MainMenuScreen.h
│   ├── GameSelectScreen.h
│   ├── AnalyticsMenuScreen.h
│   ├── GameAnalyticsScreen.h
│   ├── OverallAnalyticsScreen.h
│   ├── MathSpeedGame.h
│   ├── MathSpeedScreen.h
│   ├── MemoryMatch.h
│   ├── MemoryMatchScreen.h
│   ├── ReactionTimeGame.h
│   ├── ReactionTimeScreen.h
│   ├── StroopTestGame.h
│   └── StroopTestScreen.h
│
├── assets/                           # Game assets
│   ├── fonts/
│   │   └── JetBrainsMonoNerdFont-Bold.ttf
│   ├── images/
│   │   ├── Main-Game-Menu.png
│   │   └──ARIAL.png
│   └── sounds/
│       ├── background_music.mp3
│       ├── button_click.mp3
│       ├── score_sound.mp3
│       └── penalty_sound.mp3
│
├── README.md                         # Project documentation
├── game_data.txt                     # Saved statistics
└── *.dll                             # SFML DLL files
```


##**Authors:**

- **Muhammad Ammar Baig** - [M-AmmarBaig](https://github.com/M-AmmarBaig)
- **Ismail Nooruddin** - [IsmailNooruddin](https://github.com/IsmailNooruddin)
- **Syed Faraz Ahmed Shah** - [faraz18001](https://github.com/faraz18001)


