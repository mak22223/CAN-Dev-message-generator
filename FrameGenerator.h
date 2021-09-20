#ifndef FRAME_GENERATOR_H
#define FRAME_GENERATOR_H

#include <SPI.h>

struct CanFrame {
  unsigned long id = 0;
  unsigned char dlc = 0;
  unsigned char data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
};

class FrameGenerator {
public:
  FrameGenerator();
  FrameGenerator(byte count);
  ~FrameGenerator();
  
  byte refreshIdentificators(byte count);
  byte generateFrames(CanFrame *arr, byte count);

private:
  long *_identificators;
  unsigned char _identificators_count;
};

#endif
