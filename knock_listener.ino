#include "actions.h"
#include "usefull.h"
#include <math.h>

#define L1_MIN 0
#define L1_MAX 300
#define L2_MIN 400
#define L2_MAX 10000
#define TO1_MIN 0
#define TO1_MAX 300

uint32_t last_knock = 0;
uint32_t turn_off_at = 0;
int light_step = 0;
int turn_off_step = 0;
boolean light_just_now = false;

void knockListenerLoop()
{
  if (turn_off_at > 0 && turn_off_at < millis()) {
    debug(5, "Should turn off because of time");
    turnOff();
  }
}

void onKnock()
{
  uint32_t now = millis();
  uint32_t diff = now - last_knock;
  
  checkOutdatedValues(diff);
  
  analyzeLight(diff);
  
  if (!light_just_now && shouldTurnOff(diff)) {
    debug(5, "Should turn off because of knock");
    turnOff();
  }
  
  last_knock = now;
}

boolean analyzeLight(uint32_t diff)
{
  switch (light_step) {
    case 0: 
      light_step = 1;
      debug(5, "Light step 0 -> 1");
      break;
    
    case 1:
      if (diff < L1_MIN || L1_MAX < diff) {
        light_step = 0;
        debug(5, "Light step 1 -> 0");
        break;
      }
      
      debug(5, "Should switch on");
      debug(5, "Light step 1 -> 2");

      change230V(true);
      light_step = 2;
      light_just_now = true;
      break;
       
    case 2:
      if (L2_MIN <= diff && diff <= L2_MAX) {
        uint32_t light_time = getLightTime(diff);
        turn_off_at = millis() + light_time;
        debug(5, "Light step 2 -> 3");
        light_step = 3;
        
        debug(2, "It will turn off in %ldms", light_time);
      }
      
      break;
  }
}

boolean shouldTurnOff(uint32_t diff)
{
  if (!get230VStatus()) {
    return false;
  }
  
  if (turn_off_step == 0) {
    debug(5, "Turn off step 0 -> 1");
    
    turn_off_step = 1;
    return false;
  }
  
  debug(5, "Turn off step 1 -> 0");
  turn_off_step = 0;
  
  return TO1_MIN <= diff && diff <= TO1_MAX;
}

void turnOff()
{
  turn_off_at = 0;
  light_step = 0;
  turn_off_step = 0;
  change230V(false);
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
  
  light_just_now = false;
}

uint32_t getLightTime(uint32_t diff)
{  
  return (uint32_t) (pow(diff / 1000.0, 4.0) * 1000);
}
