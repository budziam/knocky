#include "actions.h"

#define DQ_MIN 0
#define DQ_MAX 100

#define DQAOS_FIRST_MIN 200
#define DQAOS_FIRST_MAX 400
#define DQAOS_SECOND_MIN 0
#define DQAOS_SECOND_MAX 100
int dqaos_step = 0;


uint32_t last_knock = 0;

void onKnock()
{
  uint32_t now = millis();
  uint32_t diff = now - last_knock;
  
  if (checkDoubleQuickAfterOneSlow(diff)) {
    Serial.print("Double quick after one slow!");
  }
  
  if (checkDoubleQuick(diff)) {
    Serial.print("Double quick!");
    toggle230V();
  }
  
  last_knock = now;
}

boolean checkDoubleQuick(uint32_t diff)
{
  return diff >= DQ_MIN && diff <= DQ_MAX;
}

boolean checkDoubleQuickAfterOneSlow(uint32_t diff)
{
  if (dqaos_step == 0) {
    dqaos_step = 1;
    return false;
  }
  
  if (dqaos_step == 1) {
    if (diff >= DQAOS_FIRST_MIN && diff <= DQAOS_FIRST_MAX) {
      dqaos_step = 2;
    } else {
      dqaos_step = 0;
    }
    
    return false;
  }
  
  if (dqaos_step == 2) {
    dqaos_step = 0;
    
    return diff >= DQAOS_SECOND_MIN && diff <= DQAOS_SECOND_MAX;
  }
  
  return false;
}
