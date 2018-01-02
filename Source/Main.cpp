#include "Gameboy.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <X11/Xlib.h>

int main() {
  XInitThreads();
  sf::RenderWindow window(sf::VideoMode(320, 288), "NewGBEmu!");
  window.setActive(false);

  Gameboy gameboy(window, false);
  gameboy.setFrameLimit(true);
  gameboy.insertRom("../Roms/T.gb");

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