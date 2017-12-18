#include "Gameboy.hpp"
#include <SFML/Graphics.hpp>


int main() {
  sf::RenderWindow window(sf::VideoMode(160, 144), "NewGBEmu!");
  window.setActive(false);

  Gameboy gameboy(&window, false);


  return 0;
}