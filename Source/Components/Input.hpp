//
// Created by derdro on 12/28/17.
//

#ifndef GBEMU_INPUT_HPP
#define GBEMU_INPUT_HPP

#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <functional>
#include <SFML/Window/Joystick.hpp>
#include "InputMemoryInterface.hpp"

class Gameboy;

class Input{
private:
  Gameboy* m_gameboy;
  InputMemoryInterface& m_memory;
  sf::Keyboard::Key m_buttons [8]{sf::Keyboard::A, sf::Keyboard::B, sf::Keyboard::LShift, sf::Keyboard::Space,
                                  sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Down};

  sf::Keyboard::Key m_toggleFrameLimit;
  sf::Keyboard::Key m_togglePause;

  std::string m_buttonStrings [8]{"A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN"};

  std::map<std::string, sf::Keyboard::Key> m_stringKeyMap;

  void checkForInterrupt(byte currentP1, byte bit);
  void generateStringToKeyMap();
public:
  Input(InputMemoryInterface& memory);
  void linkGameboy(Gameboy* gameboy);
  void checkP14Inputs();
  void checkP15Inputs();
  void keyPressed(sf::Keyboard::Key);

  enum P1Bits{
    P14 = 1 << 5,
    P15 = 1 << 4
  };
};
#endif //GBEMU_INPUT_HPP
