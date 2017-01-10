#ifndef ACTIONS_H
#define ACTIONS_H

/**
 * Prepare everything to work properly
 */
void setupActions();

/**
 * Toggle device connected to 230V wire
 */ 
void toggle230V();

/**
 * Change status of device connected to 230V wire
 */ 
void change230V(boolean value);

/**
 * Determine whether 230V is on or off
 */
boolean get230VStatus();

/**
 * Change status of timer indicator
 */ 
void changeTimerIndicator(boolean value);

#endif
