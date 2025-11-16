#include <iomanip>

#include <random>
#include <string>

#include <iostream>

class GameStateManger {

  // 1. this will hold the reference to the current screen which is shown.
  // 2.will mange the swticing between differetn screents.
  // 3. will handle the multiple states of the screens like pause /play etc.
  //
};

class BaseScreen {

  // oky so this is a like default template or base constrocutr type shit
  // for child classes it doens't do anything on its own but rather define
  // oothers.
};

//--------------------------------------Screens inherent From
// BaseScreen--------------------------//

class MainMenu : public BaseScreen {
  // this class will inherent from the above base screen
  // because the upper basescreen class will have multiple defined constructros.
};

class GameSelect : public BaseScreen {

  // same shit here will come back here to put the attribures and properties
};

class SetDiffScreen : public BaseScreen {
  // This class will help us to seet the difficulty from.
};

class AnalyticsScreen : public BaseScreen {};

class GameAnalyticsScreen : public BaseScreen {
  // This will show indiviudal game staes not the general overall states.
};

class PauseScreen : public BaseScreen {};

class ResultScreen : public BaseScreen {};

//---------------------Main Game Logic Nut
// Bolts--------------------------------///

class BaseGame {
  // Main game classs
  // every sub game will inheirnt from this class from on.
};

class MemoryMatch : public BaseGame {};

class MathSpeedGame : public BaseGame {};

class ReactionTime : public BaseGame {};

class CardMatchingGame : public BaseGame {};

class StroopTestGame : public BaseGame {
  // might remove this later
};

//-----------------------------Small Helper
// Classes-----------------------------///

class Button {
  // this will draw different buttons on the screen.
  // i might add methods for button pressed and actions etc
  // there might be child instances of this class like puase button menu button
  // etc
};

class StatisticsManger {};

class AssestManger {

  // this class is for grabing graphics,fonts and orther mateiral for disply.
};

class Engine {

  // this class will hanlde all the operations.
  // 1.like creating game screeens
  // 2.manges main sfml windows when we immplement the ui.
  // 3.Will direclty communicate with the screen manger class.
  // 4.Will manage global events like click and updates.
  // When this class will be triggered it will only hold a single instance of
  // screen/staticts.
  //
  //
};
