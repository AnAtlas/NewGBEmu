//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_ADDRESSRANGE_HPP
#define GBEMU_ADDRESSRANGE_HPP
#include "Types.hpp"

class AddressRange {
private:
  unsigned short m_lowerBound;
  unsigned short m_upperBound;

public:
  AddressRange(word lowerBound, word upperBound): m_lowerBound(lowerBound), m_upperBound(upperBound){}

  bool isWithin(word number){
    return (number >= m_lowerBound && number <= m_upperBound);
  }
};


#endif //GBEMU_ADDRESSRANGE_HPP
