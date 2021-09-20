#include "FrameGenerator.h"

FrameGenerator::FrameGenerator() {
  refreshIdentificators(10);
}

FrameGenerator::FrameGenerator(byte count) {
  byte initCount = count;
  if (initCount < 1 || initCount > 32) {
    initCount = 10; 
  }
  refreshIdentificators(initCount);
}

FrameGenerator::~FrameGenerator() {
  delete[] _identificators;
}

byte FrameGenerator::generateFrames(CanFrame* arr, byte count) {
  if (arr == nullptr || count > _identificators_count) {
    return 0; 
  }
//  randomSeed(analogRead(A0));
  for (byte i = 0; i < count; ++i) {
    arr[i].id = _identificators[i];
    arr[i].dlc = random(8) + 1;
    for (byte j = 0; j < arr[i].dlc; ++j) {
      arr[i].data[j] = random(256);
    }
  }
  return count;
}

byte FrameGenerator::refreshIdentificators(byte count) {
  if (count < 1 || count > 32) {
    return 1;
  }
  
  if (_identificators != nullptr) {
    delete[] _identificators;
  }

  _identificators_count = count;
  _identificators = new long[_identificators_count];
  
//  randomSeed(analogRead(A0));
  
  for (byte i = 0; i < _identificators_count; ++i) {
    //проверка на дубликат идентификатора
    bool dup = true;
    while (dup) {
      dup = false;
      long id = random(0x800);
      //первые 7 бит идентификатора не должны быть рецессивными
      if ((id & 0x7F0) == 0) {
        id &= 0x010; 
      }
      for (byte j = 0; j < i; j++) {
        if (_identificators[j] == id) {
          dup = true;
        }
      }
    }
  }
  return 0;
}
