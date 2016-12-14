#ifndef KNOCK_LISTENER_H
#define KNOCK_LISTENER_H

#include <Arduino.h>

/**
 * Prepare everything to work properly
 */
void setupKnockListener();

/**
 * Executes when knock happens
 */
void onKnock();

#endif
