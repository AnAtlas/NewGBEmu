#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

class InputInterface {
public:
  virtual bool isPressed() = 0;
};

class KeyboardInput : public InputInterface
{
private:
  sf::Keyboard::Key m_key;
public:
  KeyboardInput(sf::Keyboard::Key key) : m_key(key) {}

  bool isPressed() override
  {
    return sf::Keyboard::isKeyPressed(m_key);
  }
};

class JoystickAxisInput : public InputInterface
{
public:
  enum Value {
    Negative = -50,
    Positive = 50
  };

private:
  std::map<std::string, std::pair<sf::Joystick::Axis, Value>> m_stringToAxisMap;
  sf::Joystick::Axis m_axis;
  Value m_value;

  void generateAxisMap() {
    m_stringToAxisMap.insert(std::make_pair("DPADLEFT", std::make_pair(sf::Joystick::Axis::PovX, Negative)));
    m_stringToAxisMap.insert(std::make_pair("DPADRIGHT", std::make_pair(sf::Joystick::Axis::PovX, Positive)));
    m_stringToAxisMap.insert(std::make_pair("DPADUP", std::make_pair(sf::Joystick::Axis::PovY, Positive)));
    m_stringToAxisMap.insert(std::make_pair("DPADDOWN", std::make_pair(sf::Joystick::Axis::PovY, Negative)));
    m_stringToAxisMap.insert(std::make_pair("JOYLEFT", std::make_pair(sf::Joystick::Axis::X, Negative)));
    m_stringToAxisMap.insert(std::make_pair("JOYRIGHT", std::make_pair(sf::Joystick::Axis::X, Positive)));
    m_stringToAxisMap.insert(std::make_pair("JOYUP", std::make_pair(sf::Joystick::Axis::Y, Positive)));
    m_stringToAxisMap.insert(std::make_pair("JOYDOWN", std::make_pair(sf::Joystick::Axis::Y, Negative)));
  }
public:
  JoystickAxisInput(std::string key) {
    if (m_stringToAxisMap.size() == 0)
      generateAxisMap();
    m_axis = m_stringToAxisMap.find(key)->second.first;
    m_value = m_stringToAxisMap.find(key)->second.second;
  }

  bool isPressed() override
  {
    return ((m_value == Positive) ? sf::Joystick::getAxisPosition(0, m_axis) > Value::Positive : sf::Joystick::getAxisPosition(0, m_axis) < Value::Negative);
  }
};

class JoystickButtonInput : public InputInterface
{
private:
  int m_button;

public:
  JoystickButtonInput(int button) : m_button(button) {}

  bool isPressed() override
  {
    return sf::Joystick::isButtonPressed(0, m_button);
  }
};