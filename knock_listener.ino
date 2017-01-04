#include "actions.h"
#include "usefull.h"

#define L1_MIN 0
#define L1_MAX 300
#define L2_MIN 1000
#define L2_MAX 10000
#define TO1_MIN 0
#define TO1_MAX 300

uint32_t last_knock = 0;
uint32_t turn_off_at = 0;
int light_step = 0;
int turn_off_step = 0;

void knockListenerLoop()
{
  if (turn_off_at > 0 && turn_off_at < millis()) {
    turnOff();
  }
}

void onKnock()
{
  uint32_t now = millis();
  uint32_t diff = now - last_knock;
  
  Serial.print(now, DEC);
  Serial.print("\n");
  
  checkOutdatedValues(diff);
  
  analyzeLight(diff);
  
  if (shouldTurnOff(diff)) {
    turnOff();
  }
  
  last_knock = now;
}

void analyzeLight(uint32_t diff)
{
  switch (light_step) {
    case 0: 
      light_step = 1;
      break;
    
    case 1:
      if (diff < L1_MIN || L1_MAX < diff) {
        light_step = 0;
        break;
      }
      
      change230V(true);
      light_step = 2;
      break;
       
    case 2:
      if (L2_MIN <= diff && diff <= L2_MAX) {
        turn_off_at = millis() + getLightTime(diff);
        ardprintf("It will turn off in %dms\n", (int)getLightTime(diff));
      }
      
      light_step = 0;
      
      break;
  }
}

boolean shouldTurnOff(uint32_t diff)
{
  if (!get230VStatus()) {
    return false;
  }
  
  if (turn_off_step == 0) {
    turn_off_step = 1;
    return false;
  }
  
  turn_off_step = 0;
  
  return TO1_MIN <= diff && diff <= TO1_MAX;
}

void turnOff()
{
  change230V(false);
  turn_off_at = 0;
  light_step = 0;
  turn_off_step = 0;
}

/**
 * If user waited too long, maybe really long, we should behave
 * as if everything was at zero state
 */
void checkOutdatedValues(uint32_t diff)
{
  if (TO1_MAX < diff) {
    turn_off_step = 0;
  }
  
  if (light_step == 1 && L1_MAX < diff) {
    light_step = 0;
  }
  else if (light_step == 2 && L2_MAX < diff) {
    light_step = 0;
  }
}

uint32_t getLightTime(uint32_t diff)
{
  return diff * (diff * 37/480 - 1793/4) + 1122500/3;
}
