#include "knock_listener.h"
#include "usefull.h"

#define BUFFOR_SIZE 5
#define SPREAD_SIZE 30
#define IGNORE_MAX_BELOW 15
#define REACH_LEFT 4
#define REACH_RIGHT 6
#define MIN_INCREASE 1400
#define MIN_DECREASE 150

int buffor[BUFFOR_SIZE];
int buffor_start = 0;
int buffor_end = 0;

int spread[SPREAD_SIZE];
int spread_start = 0;
int spread_end = 0;

long long unsigned int data_index = 0;

void setupKnockDetector()
{
  buffor[0] = 0;
  spread[0] = 0;
}

void knockDetectorPushValue(int x, int y, int z)
{
  execute(z);
}

void execute(int value)
{
  data_index += 1;
  
  insert_to_buffor(value);
  
  if (get_buffor_size() < BUFFOR_SIZE) {
    return;
  }
  
  int spread = get_spread();
  insert_to_spread(spread);
  
  if (detectKnock()) {
    //ardprintf("Kck: %d %d %d(%d) %d(%d)\n", (int) data_index, node, min_left, increase, min_right, decrease);
    onKnock();
  }
}

boolean detectKnock()
{
  if (get_spread_size() < SPREAD_SIZE) {
    return false;
  }
  
  int mid_id = -(SPREAD_SIZE / 2);
  int node = get_from_spread(mid_id);
  
  if (node < IGNORE_MAX_BELOW) {
    return false;
  }
  
  if (get_from_spread(mid_id - 1) >= node || node < get_spread_max(mid_id + 1, mid_id + 1 + 2)) {
       return false;
  }
  
  int min_left = get_spread_min(mid_id - 1 - REACH_LEFT, mid_id - 1);
  int min_right = get_spread_min(mid_id + 1, mid_id + 1 + REACH_RIGHT);
  int increase = node / (float) max(1, min_left) * 100;
  int decrease = node / (float) max(1, min_right) * 100;
  
  if (increase < MIN_INCREASE || decrease < MIN_DECREASE) {
    return false;
  }
  
  return true;
}

void insert_to_buffor(int value)
{
  buffor_end = (buffor_end + 1) % BUFFOR_SIZE;
  
  if (buffor_end == buffor_start) {
    buffor_start += 1;
  }
  
  buffor[buffor_end] = value;
}

int get_buffor_size()
{
  if (buffor_end >= buffor_start) {
    return buffor_end - buffor_start + 1;
  }
  
  return BUFFOR_SIZE;
}

int get_from_buffor(int offset)
{
  if (offset > 0) {
    Serial.print("ERROR buffor positive offset\n");
    return 0;
  }
  
  if (abs(offset) >= get_buffor_size()) {
    Serial.print("ERROR buffor size\n");
    return 0;
  }

  int index = (BUFFOR_SIZE + ((buffor_end + offset) % BUFFOR_SIZE)) % BUFFOR_SIZE;
  
  return buffor[index];
}

void insert_to_spread(int value)
{
  spread_end = (spread_end + 1) % SPREAD_SIZE;
  
  if (spread_end == spread_start) {
    spread_start += 1;
  }
  
  spread[spread_end] = value;
}

int get_spread_size()
{
  if (spread_end >= spread_start) {
    return spread_end - spread_start + 1;
  }
  
  return SPREAD_SIZE;
}

int get_from_spread(int offset)
{
  if (offset > 0) {
    Serial.print("ERROR spread positive offset\n");
    return 0;
  }
  
  if (abs(offset) >= get_spread_size()) {
    Serial.print("ERROR spread size\n");
    return 0;
  }

  int index = (SPREAD_SIZE + ((spread_end + offset) % SPREAD_SIZE)) % SPREAD_SIZE;
  
  return spread[index];
}

int get_spread()
{
  int index = -BUFFOR_SIZE + 1;
  int mini = get_from_buffor(index);
  int maxi = get_from_buffor(index);
  
  for (;index <= 0; ++index) {
    mini = min(mini, get_from_buffor(index));
    maxi = max(maxi, get_from_buffor(index));
  }
  
  return abs(maxi - mini);
}

int get_spread_min(int left, int right)
{
  int mini = get_from_spread(left);
  
  for(; left <= right; ++left) {
    mini = min(mini, get_from_spread(left));
  }
  
  return mini;
}

int get_spread_max(int left, int right)
{
  int maxi = get_from_spread(left);
  
  for(; left <= right; ++left) {
    maxi = max(maxi, get_from_spread(left));
  }
  
  return maxi;
}
