#include <SFML/Graphics.hpp>
#include <thread>
#ifdef __linux__
#include <X11/Xlib.h>
#endif
#include "Gameboy.hpp"

unsigned int windowWidth, windowHeight;
bool runBios, frameLimit, debugWindow;
std::string curRom, romDir, saveDir;
void loadSettings();

int main() {
#ifdef __linux__
  XInitThreads();
#endif
  loadSettings();

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "NewGBEmu!");
  window.setActive(false);

  sf::RenderWindow debugWindow(sf::VideoMode(400,400), "Debug Window");
  window.setActive(false);

  Gameboy gameboy(window, runBios);
  gameboy.setFrameLimit(frameLimit);

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
      else if (event.type == sf::Event::KeyPressed){
        switch (event.key.code){
          case sf::Keyboard::R: gameboy.unpause(); break;
          case sf::Keyboard::S: gameboy.pause(); break;
        }
      }
    }
    while (debugWindow.pollEvent(event)){
      if (event.type == sf::Event::Closed)
        debugWindow.close();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }
  gameboy.shutDown();
  gb.join();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  return 0;
}

void loadSettings(){
  Settings& settings = Settings::getInstance();

  settings.getSetting("WindowWidth", windowWidth);
  settings.getSetting("WindowHeight", windowHeight);

  settings.getSetting("RunBios", runBios);
  settings.getSetting("FrameLimit", frameLimit);
  settings.getSetting("Debug", debugWindow);

  settings.getSetting("CurrentRom", curRom);
  settings.getSetting("RomDir", romDir);
  settings.getSetting("SaveDir", saveDir);
}