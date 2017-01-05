#ifndef BUFFER_H
#define BUFFER_H

#include <Arduino.h>
#include "debugger.h"

class Buffer {
  public:
    Buffer(const int size);
    ~Buffer();
        
    void insert(int value);
    int getSize();
    int get(int offset);
        
  protected:
    int *buffer = 0;
    int bufferSize = 0;
    int start = 0;
    int end = 0;
};

#endif
