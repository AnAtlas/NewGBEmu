//
// Created by derdro on 1/18/18.
//
#include "SquareChannel.hpp"

SquareChannel::SquareChannel(AudioMemoryInterface &memory, bool hasSweep)
    : SoundChannel(memory), m_hasSweep(hasSweep){

}