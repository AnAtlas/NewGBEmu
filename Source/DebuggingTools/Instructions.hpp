//
// Created by derdro on 12/27/17.
//

#ifndef GBEMU_INSTRUCTIONS_HPP
#define GBEMU_INSTRUCTIONS_HPP
#include <string>
#include <vector>

struct Instruction{
  int paramaterAmount;
  std::string tokenString;
  Instruction(int parmAmount, std::string str){
    paramaterAmount = parmAmount;
    tokenString = str;
  }
};

static std::vector<Instruction> generateInstructions(){
  std::vector<Instruction> ins;
  ins.emplace_back(Instruction(0,"NOP"));

  return ins;
}
#endif //GBEMU_INSTRUCTIONS_HPP
