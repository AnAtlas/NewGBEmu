#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

class InputInterface {
public:
  virtual bool isPressed() const = 0;
  virtual bool isPressed(sf::Keyboard::Key key) const = 0;
  virtual bool isPressed(int buttonCode) const = 0;
  virtual bool isPressed(sf::Joystick::Axis axis, float position) const = 0;
  virtual bool isKey(sf::Keyboard::Key key) const = 0;
  virtual bool isKey(sf::Joystick::Axis axis) const = 0;
  virtual bool isKey(int buttonCode) const = 0;
};

class KeyboardInput : public InputInterface
{
private:
  sf::Keyboard::Key m_key;
public:
  explicit KeyboardInput(sf::Keyboard::Key key) : m_key(key) {}

  bool isPressed() const override {
    return sf::Keyboard::isKeyPressed(m_key);
  }

  bool isPressed(sf::Keyboard::Key key) const override {
    return (key == m_key) ? sf::Keyboard::isKeyPressed(m_key) : false;
  }

  bool isPressed(sf::Joystick::Axis axis, float position) const override{
    return false;
  }

  bool isPressed(int buttonCode) const override{
    return false;
  }

  bool isKey(sf::Keyboard::Key key) const override{
    return (m_key == key);
  }

  bool isKey(sf::Joystick::Axis axis) const override{
    return false;
  }

  bool isKey(int buttonCode) const override{
    return false;
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
  explicit JoystickAxisInput(std::string key): m_axis(sf::Joystick::X), m_value(Value::Positive) {
    if (m_stringToAxisMap.size() == 0)
      generateAxisMap();
    m_axis = m_stringToAxisMap.find(key)->second.first;
    m_value = m_stringToAxisMap.find(key)->second.second;
  }

  bool isPressed() const override
  {
    return ((m_value == Positive) ? sf::Joystick::getAxisPosition(0, m_axis) > Value::Positive : sf::Joystick::getAxisPosition(0, m_axis) < Value::Negative);
  }

  bool isPressed(sf::Keyboard::Key key) const override {
    return false;
  }

  bool isPressed(sf::Joystick::Axis axis, float position) const override{
    return (axis == m_axis) ? isPressed() : false;
  }

  bool isPressed(int buttonCode) const override{
    return false;
  }

  bool isKey(sf::Keyboard::Key key) const override{
    return false;
  }

  bool isKey(sf::Joystick::Axis axis) const override{
    return (m_axis == axis);
  }

  bool isKey(int buttonCode) const override{
    return false;
  }
};

class JoystickButtonInput : public InputInterface
{
private:
  int m_button;

public:
  explicit JoystickButtonInput(int button) : m_button(button) {}

  bool isPressed() const override
  {
    return sf::Joystick::isButtonPressed(0, m_button);
  }

  bool isPressed(sf::Keyboard::Key key) const override {
    return false;
  }

  bool isPressed(sf::Joystick::Axis axis, float position) const override{
    return false;
  }

  bool isPressed(int buttonCode) const override{
    return (buttonCode == m_button) ? isPressed() : false;
  }

  bool isKey(sf::Keyboard::Key key) const override{
    return false;
  }

  bool isKey(sf::Joystick::Axis axis) const override{
    return false;
  }

  bool isKey(int buttonCode) const override{
    return buttonCode == m_button;
  }
};