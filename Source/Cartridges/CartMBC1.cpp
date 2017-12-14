//
// Created by derdro on 12/14/17.
//

#include "CartMBC1.hpp"

CartMBC1::CartMBC1(std::string romPath)
  :Cartridge(romPath), m_ramEnabled(false), m_bankingMode(BankingMode::ROM_BANKING_MODE)
{

}

bool CartMBC1::loadRamBankX(byte ramBankIndex) {

}

bool CartMBC1::loadCartridge() {
  return (loadRomBank0() && loadRomBankX(1) && loadRamBankX(0));
}