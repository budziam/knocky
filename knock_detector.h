#ifndef KNOCK_DETECTOR_H
#define KNOCK_DETECTOR_H

/**
 * Prepare everything to work properly
 */
void setupKnockDetector();

/**
 * Send accelerator values to knock detecor
 */ 
void knockDetectorPushValues(int x, int y, int z);

#endif
