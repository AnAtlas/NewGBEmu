#include "Gameboy.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <X11/Xlib.h>

int main() {
  XInitThreads();
  sf::RenderWindow window(sf::VideoMode(160, 144), "NewGBEmu!");
  window.setActive(false);

  Gameboy gameboy(window, false);

  gameboy.insertRom("TestRom/03-op sp,hl.gb");

  std::thread gb(&Gameboy::play, &gameboy);

  sf::Event event{};
  while (window.isOpen()){
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }

  gameboy.shutDown();
  gb.join();
  sf::sleep(sf::milliseconds(100));

  return 0;
}