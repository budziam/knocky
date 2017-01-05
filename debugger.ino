#define DEBUG_LEVEL 3

#include <stdarg.h>
#include <Arduino.h>

void debug(int level, char *fmt, ...)
{
  if (DEBUG_LEVEL < level) {
    return;
  }
  
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 128, fmt, args);
  va_end (args);
  Serial.println(buf);
}

#undef ARDBUFFER
