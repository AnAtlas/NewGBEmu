//
// Created by derdro on 1/3/18.
//

#ifndef GBEMU_SETTINGS_HPP
#define GBEMU_SETTINGS_HPP
#include <string>
#include <fstream>
#include <memory>
#include <algorithm>

class Settings{
private:
  static Settings m_instance;
  std::fstream m_settingsFile;
  Settings(){
    m_settingsFile.open("Settings.ini", std::ios::in);
  }

  bool getKeyLine(const std::string& key, std::string& retLine){
    std::string line;
    std::string lineKey;
    std::string keyUpper = key;
    std::transform(keyUpper.begin(), keyUpper.end(), keyUpper.begin(), toupper);

    m_settingsFile.clear();
    m_settingsFile.seekg(0, std::ios::beg);
    while (!m_settingsFile.eof()){
      std::getline(m_settingsFile, line);
      lineKey = line.substr(0, line.find('='));
      std::transform(lineKey.begin(), lineKey.end(), lineKey.begin(), toupper);
      if (lineKey == keyUpper){
        retLine = line;
        return true;
      }
    }
    return false;
  }

  void getValueLine(std::string& line, std::string& value){
    value = line.substr(line.find('=') + 1, std::string::npos);
  }

public:
  static Settings& getInstance(){
    static Settings m_instance;
    return m_instance;
  }
  bool getSetting(const std::string& key, bool& value){
    std::string line;
    std::string valueStr;
    if (!getKeyLine(key, line))
      return false;
    getValueLine(line, valueStr);
    std::transform(valueStr.begin(), valueStr.end(), valueStr.begin(), tolower);
    if (valueStr == "false")
      value = false;
    if (valueStr == "true")
      value = true;
    return true;
  }

  bool getSetting(const std::string& key, unsigned int& value){
    std::string line;
    std::string valueStr;
    if (!getKeyLine(key, line))
      return false;
    getValueLine(line, valueStr);
    value = (unsigned int)std::stoi(valueStr, nullptr);
    return true;
  }

  bool getSetting(const std::string& key, std::string& value){
    std::string line;
    std::string valueStr;
    if (!getKeyLine(key, line))
      return false;
    getValueLine(line, value);
    return true;
  }

  bool clearSetting(const std::string& key){
    return true;
  }
};
#endif //GBEMU_SETTINGS_HPP
