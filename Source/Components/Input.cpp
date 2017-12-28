//
// Created by derdro on 12/28/17.
//
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <bitset>
#include "Input.hpp"

Input::Input(InputMemoryInterface& memory): m_memory(memory)
{
  m_keyStart = sf::Keyboard::Space;
  m_keySelect = sf::Keyboard::LShift;
  m_keyA = sf::Keyboard::X;
  m_keyB = sf::Keyboard::Z;
  m_keyDown = sf::Keyboard::Down;
  m_keyUp = sf::Keyboard::Up;
  m_keyLeft = sf::Keyboard::Left;
  m_keyRight = sf::Keyboard::Right;
}

void Input::checkInputs() {
  byte output = 0x0F;
  byte currentP1 = m_memory.readP1();
  if (~currentP1 & (byte)0b00010000){
    for (int i = 0; i < 4; i++){
      if (sf::Keyboard::isKeyPressed(*m_rowP14[i]))
        checkForInterrupt(currentP1, (byte)i);
        resetBit(output, (byte)i);
    }
  }
  if (~currentP1 & (byte)0b00100000){
    for (int i = 0; i < 4; i++){
      if (sf::Keyboard::isKeyPressed(*m_rowP15[i]))
        checkForInterrupt(currentP1, (byte)i);
        resetBit(output, (byte)i);
    }
  }
  m_memory.writeP1Inputs(output);
}

void Input::checkForInterrupt(byte currentP1, byte bit){
  if (!(~currentP1 & (byte)1 << (3 - bit)))
    m_memory.requestInputInterrupt();
}

void Input::resetBit(byte& val, byte bit) {
  byte tmp = (byte)1 << (3 - bit);
  val &= ~tmp;
}