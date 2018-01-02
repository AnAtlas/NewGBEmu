//
// Created by derdro on 12/28/17.
//

#ifndef GBEMU_INPUT_HPP
#define GBEMU_INPUT_HPP

#include <SFML/Window/Keyboard.hpp>
#include "InputMemoryInterface.hpp"

class Input{
private:
  InputMemoryInterface& m_memory;
  sf::Keyboard::Key m_keyStart;
  sf::Keyboard::Key m_keySelect;
  sf::Keyboard::Key m_keyA;
  sf::Keyboard::Key m_keyB;
  sf::Keyboard::Key m_keyDown;
  sf::Keyboard::Key m_keyUp;
  sf::Keyboard::Key m_keyLeft;
  sf::Keyboard::Key m_keyRight;

  sf::Keyboard::Key* m_rowP14 [4]{&m_keyA, &m_keyB, &m_keySelect, &m_keyStart};
  sf::Keyboard::Key* m_rowP15 [4]{&m_keyRight, &m_keyLeft, &m_keyUp, &m_keyDown};

  void checkForInterrupt(byte currentP1, byte bit);
public:
  Input(InputMemoryInterface& memory);
  void checkP14Inputs();
  void checkP15Inputs();

  enum P1Bits{
    P14 = 1 << 5,
    P15 = 1 << 4
  };
};
#endif //GBEMU_INPUT_HPP
