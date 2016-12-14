#define BUFFOR_SIZE 5
#define SPREAD_SIZE 30
#define IGNORE_MAX_BELOW 15
#define MIN_INCREASE 2000
#define MIN_DECREASE 200
#define KNOCK_SIZE 20

int buffor[BUFFOR_SIZE];
int buffor_start = 0;
int buffor_end = 0;

int spread[SPREAD_SIZE];
int spread_start = 0;
int spread_end = 0;

long long unsigned int data_index = 0;
int last_knock_index = 0;

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
  
  calculate();
}

void calculate()
{
  if (get_spread_size() < SPREAD_SIZE) {
    return;
  }
 
   if (data_index < last_knock_index + KNOCK_SIZE) {
    return;
  }
    
  if (get_from_spread(-15) >= get_from_spread(-14) || get_from_spread(-14) < get_from_spread(-13)) {
       return;
  }
  
  int node = get_from_spread(-14);
  
  if (node < IGNORE_MAX_BELOW) {
    return;
  }
  
  int min_left = get_spread_min(-19, -14);
  int min_right = get_spread_min(-12, -4);
  int increase = node / (float) max(1, min_left) * 100;
  int decrease = node / (float) max(1, min_right) * 100;
    
  if (increase < MIN_INCREASE || decrease < MIN_DECREASE) {
    return;
  }
    
  last_knock_index = data_index;
  
  
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
