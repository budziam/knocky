#ifndef KNOCK_LISTENER_H
#define KNOCK_LISTENER_H

#include <Arduino.h>
#include "debugger.h"

/**
 * Executes when knock happens
 */
void onKnock();

void knockListenerLoop();

#endif
