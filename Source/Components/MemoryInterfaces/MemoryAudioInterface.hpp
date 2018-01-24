//
// Created by derdro on 1/23/18.
//

#ifndef GBEMU_MEMORYAUDIOINTERFACE_HPP
#define GBEMU_MEMORYAUDIOINTERFACE_HPP

class MemoryAudioInterface
{
public:
  virtual void initTriggered(int channelIndex) = 0;
};
#endif //GBEMU_MEMORYAUDIOINTERFACE_HPP
