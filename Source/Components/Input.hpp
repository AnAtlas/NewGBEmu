//
// Created by derdro on 12/28/17.
//

#ifndef GBEMU_INPUT_HPP
#define GBEMU_INPUT_HPP

#include <map>
#include <vector>
#include <memory>
#include "../Utilities/InputInterface.hpp"
#include "MemoryInterfaces/InputMemoryInterface.hpp"

class Gameboy;

enum class InputAction{
  A = 0,
  B = 1,
  SELECT = 2,
  START = 3,
  RIGHT = 4,
  LEFT = 5,
  UP = 6,
  DOWN = 7,
  NONE = 8,
  TOGGLE_FRAME_LIMIT = 9,
  TOGGLE_PAUSE = 10,
  SET_SPEED_2X = 11,
  SET_SPEED_1X = 12
};

class InputManager{
private:
  InputAction m_action;
  std::string m_actionName;
  std::vector<std::shared_ptr<InputInterface>> m_inputs;

public:
  InputManager(InputAction input, std::string& actionName)
    : m_action(input)
  {
  }

  ~InputManager(){
    m_inputs.clear();
  }

  void addInput(std::shared_ptr<InputInterface> input){
    m_inputs.push_back(input);
  }

  bool isPressed(){
    for (const auto& i : m_inputs){
      if (i->isPressed())
        return true;
    }
    return false;
  }

  bool isPressed(sf::Keyboard::Key key){
    for (const auto& i : m_inputs){
      if (i->isPressed(key))
        return true;
    }
    return false;
  }

  bool isKey(sf::Keyboard::Key key){
    for (const auto& i : m_inputs){
      if (i->isPressed(key))
        return true;
    }
    return false;
  }

  bool isPressed(sf::Joystick::Axis axis, float position){
    for (const auto& i : m_inputs){
      if (i->isPressed(axis, position))
        return true;
    }
    return false;
  }

  bool isPressed(int buttonCode){
    for (const auto& i : m_inputs){
      if (i->isPressed(buttonCode))
        return true;
    }
    return false;
  }
};


class Input{
private:
  Gameboy* m_gameboy;
  InputMemoryInterface& m_memory;

  std::map<InputAction, InputManager> m_inputs;

  std::string m_buttonStrings [13]{"A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN", "","ToggleFrameLimit", "TogglePause", "Speed2x", "Speed1x"};

  std::map<std::string, sf::Keyboard::Key> m_stringKeyMap;

  void checkForInterrupt(byte currentP1, byte bit);
  void generateStringToKeyMap();
  void delegateOtherInputPress(InputAction input);
public:
  explicit Input(InputMemoryInterface& memory);
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
