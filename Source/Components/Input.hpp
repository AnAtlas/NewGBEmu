//
// Created by derdro on 12/28/17.
//

#ifndef GBEMU_INPUT_HPP
#define GBEMU_INPUT_HPP

#include <map>
#include <vector>
#include "../Utilities/InputInterface.hpp"
#include "InputMemoryInterface.hpp"

class Gameboy;

class Input{
private:
  enum GameboyInput {
    A = 0,
    B = 1,
    SELECT = 2,
    START = 3,
    RIGHT = 4,
    LEFT = 5,
    UP = 6,
    DOWN = 7
  };

  Gameboy* m_gameboy;
  InputMemoryInterface& m_memory;
  sf::Keyboard::Key m_buttons [8]{sf::Keyboard::A, sf::Keyboard::B, sf::Keyboard::LShift, sf::Keyboard::Space,
                                  sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Down};

  std::map<GameboyInput, std::vector<InputInterface*>> m_gameboyInputs;
  sf::Keyboard::Key m_toggleFrameLimit;
  sf::Keyboard::Key m_togglePause;

  std::string m_buttonStrings [8]{"A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN"};

  std::map<std::string, sf::Keyboard::Key> m_stringKeyMap;

  void checkForInterrupt(byte currentP1, byte bit);
  void generateStringToKeyMap();
public:
  Input(InputMemoryInterface& memory);
  ~Input();
  void linkGameboy(Gameboy* gameboy);
  void checkP14Inputs();
  void checkP15Inputs();
  void keyPressed(sf::Keyboard::Key);
  void joystickButtonPressed(int buttonCode);

  enum P1Bits{
    P14 = 1 << 5,
    P15 = 1 << 4
  };
};
#endif //GBEMU_INPUT_HPP
