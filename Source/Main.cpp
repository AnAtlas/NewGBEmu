#include <SFML/Graphics.hpp>
#include <thread>
#include <X11/Xlib.h>

#include "Gameboy.hpp"


int main() {
  XInitThreads();
  Settings& settings = Settings::getInstance();

  unsigned int windowWidth, windowHeight;
  settings.getSetting("WindowWidth", windowWidth);
  settings.getSetting("WindowHeight", windowHeight);
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "NewGBEmu!");
  window.setActive(false);

  bool runBios;
  settings.getSetting("RunBios", runBios);
  Gameboy gameboy(window, runBios);

  bool frameLimit;
  settings.getSetting("FrameLimit", frameLimit);
  gameboy.setFrameLimit(frameLimit);
  std::string curRom, romDir, saveDir;
  settings.getSetting("CurrentRom", curRom);
  settings.getSetting("RomDir", romDir);
  settings.getSetting("SaveDir", saveDir);
  gameboy.insertRom(romDir + curRom);

  std::thread gb(&Gameboy::play, &gameboy);

  sf::Event event{};
  while (window.isOpen()){
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::Resized){
        window.setSize(sf::Vector2u(event.size.width, event.size.height));
      }
    }
  }

  gameboy.shutDown();
  gb.join();
  sf::sleep(sf::milliseconds(100));

  return 0;
}