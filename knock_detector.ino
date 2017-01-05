#include "knock_detector.h"

#define SPREAD_SIZE 30
#define RAW_DATA_SIZE 4
#define IGNORE_MAX_BELOW 15
#define REACH_LEFT 5
#define REACH_RIGHT 8
#define MIN_INCREASE 1400
#define MIN_DECREASE 150
#define KNOCK_SIZE 8

KnockDetector::KnockDetector(char _id)
{
  id = _id;
  spread = new Buffer(SPREAD_SIZE);
  rawData = new Buffer(RAW_DATA_SIZE);
}

KnockDetector::~KnockDetector()
{
  delete spread;
  delete rawData;
}

boolean KnockDetector::push(int value)
{
  data_index += 1;
  
  rawData->insert(value);
  
  if (rawData->getSize() < RAW_DATA_SIZE) {
    return false;
  }
  
  spread->insert(getSpread());
  
  return detectKnock();
}

boolean KnockDetector::detectKnock()
{
  if (spread->getSize() < SPREAD_SIZE) {
    return false;
  }
  
  if (data_index - last_knock < KNOCK_SIZE) {
    return false;
  }
  
  int mid_id = -(SPREAD_SIZE / 2);
  int node = spread->get(mid_id);
  
  if (node < IGNORE_MAX_BELOW) {
    return false;
  }
  
  if (spread->get(mid_id - 1) >= node || node < getSpreadMax(mid_id + 1, mid_id + 1 + 2)) {
       return false;
  }
  
  int min_left = getSpreadMin(mid_id - 1 - REACH_LEFT, mid_id - 1);
  int min_right = getSpreadMin(mid_id + 1, mid_id + 1 + REACH_RIGHT);
  int increase = node / (float) max(1, min_left) * 100;
  int decrease = node / (float) max(1, min_right) * 100;
  
  if (increase < MIN_INCREASE || decrease < MIN_DECREASE) {
    return false;
  }
  
  last_height = node;
  last_knock = data_index;
  
  debug(4, "[%c] Knock#%lu (%lu): %d %d(%d) %d(%d)", id, data_index, millis(), node, min_left, increase, min_right, decrease);
  
  return true;
}

int KnockDetector::getSpread()
{
  int index = -RAW_DATA_SIZE + 1;
  int mini = rawData->get(index);
  int maxi = rawData->get(index);
  
  for (;index <= 0; ++index) {
    mini = min(mini, rawData->get(index));
    maxi = max(maxi, rawData->get(index));
  }
  
  return abs(maxi - mini);
}

int KnockDetector::getSpreadMin(int left, int right)
{
  int mini = spread->get(left);
  
  for(; left <= right; ++left) {
    mini = min(mini, spread->get(left));
  }
  
  return mini;
}

int KnockDetector::getSpreadMax(int left, int right)
{
  int maxi = spread->get(left);
  
  for(; left <= right; ++left) {
    maxi = max(maxi, spread->get(left));
  }
  
  return maxi;
}

int KnockDetector::getLastHeight()
{
  return last_height;
}
