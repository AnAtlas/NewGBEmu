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
  for (int i = 0; i < 8; ++i){
    m_gameboyInputs.insert(std::make_pair( (GameboyInput)i, std::vector<InputInterface*>()));
    if (settings.getSetting(m_buttonStrings[i], temp, std::string("keyboard"))){
      std::transform(temp.begin(), temp.end(), temp.begin(), toupper);
      auto it = m_stringKeyMap.find(temp);
      if (it != m_stringKeyMap.end()) {
        m_gameboyInputs.find((GameboyInput)i)->second.push_back(new KeyboardInput(it->second));
      }
      else
        settings.clearSetting(temp);
    }
  }
  if (settings.getSetting("ToggleFrameLimit", temp)){
    std::transform(temp.begin(), temp.end(), temp.begin(), toupper);
    auto it = m_stringKeyMap.find(temp);
    if (it != m_stringKeyMap.end())
      m_toggleFrameLimit = it->second;
    else
      settings.clearSetting(temp);
  }
  if (settings.getSetting("TogglePause", temp)){
    std::transform(temp.begin(), temp.end(), temp.begin(), toupper);
    auto it = m_stringKeyMap.find(temp);
    if (it != m_stringKeyMap.end())
      m_togglePause= it->second;
    else
      settings.clearSetting(temp);
  }

  //Check for Joystick
  if (sf::Joystick::isConnected(0)) {
    for (int i = 0; i < 8; ++i) {
      if (settings.getSetting(m_buttonStrings[i], temp, std::string("controller"))) {
        std::transform(temp.begin(), temp.end(), temp.begin(), toupper);
        try {
          int x = std::stoi(temp);
          m_gameboyInputs.find((GameboyInput)i)->second.push_back(new JoystickButtonInput(x));
        }
        catch (std::exception&) {
          m_gameboyInputs.find((GameboyInput)i)->second.push_back(new JoystickAxisInput(temp));
        }
      }
      else
        settings.clearSetting(temp);
    }
  }
}

Input::~Input() {

  //Delete all created inputs
  for (auto a : m_gameboyInputs) {
    for (auto b : a.second) {
      delete b;
    }
    a.second.clear();
  }
  m_gameboyInputs.clear();
}

void Input::linkGameboy(Gameboy* gameboy){
  m_gameboy = gameboy;
}

void Input::checkP14Inputs() {
  byte output = 0x0F;
  byte currentP1 = m_memory.readP1();
  for (byte i = 3; i < 255; --i){
    for (auto input : m_gameboyInputs.find((GameboyInput)i)->second) {
      if (input->isPressed()) {
        checkForInterrupt(currentP1, i);
        output &= ~(1 << i);
      }
    }
  }
  m_memory.writeP1Inputs(output);
}

void Input::checkP15Inputs() {
  byte output = 0x0F;
  byte currentP1 = m_memory.readP1();
  for (byte i = 3; i < 255; --i){
    for (auto input : m_gameboyInputs.find((GameboyInput)(i+4))->second) {
      if (input->isPressed()) {
        checkForInterrupt(currentP1, i);
        output &= ~(1 << i);
      }
    }
  }
  m_memory.writeP1Inputs(output);
}

void Input::checkForInterrupt(byte currentP1, byte bit){
  if (currentP1 & (1 << bit))
    m_memory.requestInputInterrupt();
}

void Input::keyPressed(sf::Keyboard::Key key) {
  if (key == m_toggleFrameLimit)
    m_gameboy->toggleFrameLimit();
  else if (key == m_togglePause)
    m_gameboy->togglePause();
}

void Input::joystickButtonPressed(int buttonCode) {

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