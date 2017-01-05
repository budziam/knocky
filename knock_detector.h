#ifndef KNOCK_DETECTOR_H
#define KNOCK_DETECTOR_H

#include <Arduino.h>
#include "buffer.h"
#include "debugger.h"

class KnockDetector {
  public:
    KnockDetector(char id);
    ~KnockDetector();
        
    /**
     * Pushes accelerator value, return true if knock detected
     */ 
    boolean push(int value);
    
    int getLastHeight();
        
  protected:
    char id = 0;
    uint32_t data_index = 0;
    uint32_t last_knock = 0;
    int last_height = 0;
    
    Buffer *rawData = 0;
    Buffer *spread = 0;
    
    boolean detectKnock();
    int getSpread();
    int getSpreadMin(int left, int right);
    int getSpreadMax(int left, int right);
};

#endif
