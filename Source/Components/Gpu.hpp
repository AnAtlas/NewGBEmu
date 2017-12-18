//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_GPU_HPP
#define NEWGBEMU_GPU_HPP

#include "GpuMemoryInterface.hpp"
class Gpu
{
private:

  GpuMemoryInterface& m_memory;
public:
    Gpu(GpuMemoryInterface& memory) : m_memory(memory){

    }
};
#endif //NEWGBEMU_GPU_HPP
