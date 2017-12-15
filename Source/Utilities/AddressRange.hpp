//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_ADDRESSRANGE_HPP
#define GBEMU_ADDRESSRANGE_HPP
#include "Types.hpp"

class AddressRange {
private:
  word m_lowerBound;
  word m_upperBound;

public:
  AddressRange(word lowerBound, word upperBound): m_lowerBound(lowerBound), m_upperBound(upperBound){}

  bool contains(word number)const {
    return (number >= m_lowerBound && number <= m_upperBound);
  }

  word start() const {
    return m_lowerBound;
  }
};


#endif //GBEMU_ADDRESSRANGE_HPP
