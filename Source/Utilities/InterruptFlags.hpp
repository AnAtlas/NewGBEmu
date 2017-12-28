//
// Created by derdro on 12/28/17.
//

#ifndef GBEMU_INTERRUPTFLAGS_HPP
#define GBEMU_INTERRUPTFLAGS_HPP

enum IntFlags{
  VBLANK = 1,
  LCD_STAT = 1 << 1,
  TIMER = 1 << 2,
  SERIAL = 1 << 3,
  JOYPAD = 1 << 4
};

#endif //GBEMU_INTERRUPTFLAGS_HPP
