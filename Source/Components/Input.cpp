//
// Created by derdro on 12/28/17.
//
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <sstream>
#include "Input.hpp"
#include "../Utilities/Settings.hpp"
#include "../Gameboy.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

Input::Input(InputMemoryInterface& memory): m_memory(memory)
{
  generateStringToKeyMap();
  //Check Settings file for changed controls
  Settings& settings = Settings::getInstance();
  std::string temp;
  for (int i = 0; i < 13; ++i){
    m_inputs.insert(std::make_pair((InputAction)i, InputManager((InputAction)i, m_buttonStrings[i])));
    if (settings.getSetting(m_buttonStrings[i], temp, std::string("keyboard"))){
      std::transform(temp.begin(), temp.end(), temp.begin(), toupper);
      auto it = m_stringKeyMap.find(temp);
      if (it != m_stringKeyMap.end()) {
        m_inputs.find((InputAction)i)->second.addInput(std::make_shared<KeyboardInput>(it->second));
      }
      else
        settings.clearSetting(temp);
    }
    if (sf::Joystick::isConnected(0)) {
      if (settings.getSetting(m_buttonStrings[i], temp, std::string("controller"))) {
        std::transform(temp.begin(), temp.end(), temp.begin(), toupper);
        try {
          int x = std::stoi(temp);
          m_inputs.find((InputAction)i)->second.addInput(std::make_shared<JoystickButtonInput>(x));
        }
        catch (std::exception&) {
          m_inputs.find((InputAction)i)->second.addInput(std::make_shared<JoystickAxisInput>(temp));
        }
      }
      else
        settings.clearSetting(temp);
    }
  }
}

void Input::linkGameboy(Gameboy* gameboy){
  m_gameboy = gameboy;
}

void Input::checkP14Inputs() {
  byte output = 0x0F;
  byte currentP1 = m_memory.readP1();
  for (byte i = 3; i < 255; --i){
    if (m_inputs.find((InputAction)i)->second.isPressed()) {
      checkForInterrupt(currentP1, i);
      output &= ~(1 << i);
    }
  }
  m_memory.writeP1Inputs(output);
}

void Input::checkP15Inputs() {
  byte output = 0x0F;
  byte currentP1 = m_memory.readP1();
  for (byte i = 3; i < 255; --i){
    if (m_inputs.find((InputAction)(i+4))->second.isPressed()) {
      checkForInterrupt(currentP1, i);
      output &= ~(1 << i);
    }
  }
  m_memory.writeP1Inputs(output);
}

void Input::checkForInterrupt(byte currentP1, byte bit){
  if (currentP1 & (1 << bit))
    m_memory.requestInputInterrupt();
}

void Input::keyPressed(sf::Keyboard::Key key) {
  InputAction match = InputAction::NONE;
  for (auto inMan : m_inputs){
    if (inMan.second.isKey(key)) {
      match = inMan.first;
      break;
    }
  }
  delegateOtherInputPress(match);
}

void Input::joystickButtonPressed(int buttonCode) {
  InputAction match = InputAction::NONE;
  for (auto inMan : m_inputs){
    if (inMan.second.isPressed(buttonCode)) {
      match = inMan.first;
      break;
    }
  }
  delegateOtherInputPress(match);
}

void Input::delegateOtherInputPress(InputAction input) {
  switch (input){
    case InputAction::TOGGLE_FRAME_LIMIT: m_gameboy->toggleFrameLimit(); break;
    case InputAction::TOGGLE_PAUSE: m_gameboy->togglePause(); break;
    case InputAction::SET_SPEED_2X: m_gameboy->setSpeed(2.0); break;
    case InputAction::SET_SPEED_1X: m_gameboy->setSpeed(1.0); break;
    default: ;
  }
}

void Input::generateStringToKeyMap(){
  m_stringKeyMap.emplace(std::make_pair("A", sf::Keyboard::A));
  m_stringKeyMap.emplace(std::make_pair("B", sf::Keyboard::B));
  m_stringKeyMap.emplace(std::make_pair("C", sf::Keyboard::C));
  m_stringKeyMap.emplace(std::make_pair("D", sf::Keyboard::D));
  m_stringKeyMap.emplace(std::make_pair("E", sf::Keyboard::E));
  m_stringKeyMap.emplace(std::make_pair("F", sf::Keyboard::F));
  m_stringKeyMap.emplace(std::make_pair("G", sf::Keyboard::G));
  m_stringKeyMap.emplace(std::make_pair("H", sf::Keyboard::H));
  m_stringKeyMap.emplace(std::make_pair("I", sf::Keyboard::I));
  m_stringKeyMap.emplace(std::make_pair("J", sf::Keyboard::J));
  m_stringKeyMap.emplace(std::make_pair("K", sf::Keyboard::K));
  m_stringKeyMap.emplace(std::make_pair("L", sf::Keyboard::L));
  m_stringKeyMap.emplace(std::make_pair("M", sf::Keyboard::M));
  m_stringKeyMap.emplace(std::make_pair("N", sf::Keyboard::N));
  m_stringKeyMap.emplace(std::make_pair("O", sf::Keyboard::O));
  m_stringKeyMap.emplace(std::make_pair("P", sf::Keyboard::P));
  m_stringKeyMap.emplace(std::make_pair("Q", sf::Keyboard::Q));
  m_stringKeyMap.emplace(std::make_pair("R", sf::Keyboard::R));
  m_stringKeyMap.emplace(std::make_pair("S", sf::Keyboard::S));
  m_stringKeyMap.emplace(std::make_pair("T", sf::Keyboard::T));
  m_stringKeyMap.emplace(std::make_pair("U", sf::Keyboard::U));
  m_stringKeyMap.emplace(std::make_pair("V", sf::Keyboard::V));
  m_stringKeyMap.emplace(std::make_pair("W", sf::Keyboard::W));
  m_stringKeyMap.emplace(std::make_pair("X", sf::Keyboard::X));
  m_stringKeyMap.emplace(std::make_pair("Y", sf::Keyboard::Y));
  m_stringKeyMap.emplace(std::make_pair("Z", sf::Keyboard::Z));

  m_stringKeyMap.emplace(std::make_pair("1", sf::Keyboard::Num1));
  m_stringKeyMap.emplace(std::make_pair("2", sf::Keyboard::Num2));
  m_stringKeyMap.emplace(std::make_pair("3", sf::Keyboard::Num3));
  m_stringKeyMap.emplace(std::make_pair("4", sf::Keyboard::Num4));
  m_stringKeyMap.emplace(std::make_pair("5", sf::Keyboard::Num5));
  m_stringKeyMap.emplace(std::make_pair("6", sf::Keyboard::Num6));
  m_stringKeyMap.emplace(std::make_pair("7", sf::Keyboard::Num7));
  m_stringKeyMap.emplace(std::make_pair("8", sf::Keyboard::Num8));
  m_stringKeyMap.emplace(std::make_pair("9", sf::Keyboard::Num9));
  m_stringKeyMap.emplace(std::make_pair("0", sf::Keyboard::Num0));


  m_stringKeyMap.emplace(std::make_pair("RIGHT", sf::Keyboard::Right));
  m_stringKeyMap.emplace(std::make_pair("LEFT", sf::Keyboard::Left));
  m_stringKeyMap.emplace(std::make_pair("UP", sf::Keyboard::Up));
  m_stringKeyMap.emplace(std::make_pair("DOWN", sf::Keyboard::Down));

  m_stringKeyMap.emplace(std::make_pair("SPACE", sf::Keyboard::Space));
  m_stringKeyMap.emplace(std::make_pair("RETURN", sf::Keyboard::Return));
  m_stringKeyMap.emplace(std::make_pair("LSHIFT", sf::Keyboard::LShift));
  m_stringKeyMap.emplace(std::make_pair("RSHIFT", sf::Keyboard::RShift));
  m_stringKeyMap.emplace(std::make_pair("BACKSPACE", sf::Keyboard::BackSpace));
  m_stringKeyMap.emplace(std::make_pair("LCONTROL", sf::Keyboard::LControl));
  m_stringKeyMap.emplace(std::make_pair("RCONTROL", sf::Keyboard::RControl));
  m_stringKeyMap.emplace(std::make_pair("EQUAL", sf::Keyboard::Equal));
  m_stringKeyMap.emplace(std::make_pair("DASH", sf::Keyboard::Dash));
}