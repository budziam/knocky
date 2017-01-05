#include "buffer.h"

Buffer::Buffer(const int size)
{
  bufferSize = size;
  buffer = new int [bufferSize];
  buffer[0] = 0;
}

Buffer::~Buffer()
{
  delete buffer;
}

void Buffer::insert(int value)
{
  end = (end + 1) % bufferSize;
  
  if (end == start) {
    start += 1;
  }
  
  buffer[end] = value;
}

int Buffer::getSize()
{
  if (end >= start) {
    return end - start + 1;
  }
  
  return bufferSize;
}

int Buffer::get(int offset)
{
  if (offset > 0) {
    debug(1, "ERROR buffer positive offset");
    return 0;
  }
  
  if (abs(offset) >= getSize()) {
    debug(1, "ERROR buffer size");
    return 0;
  }

  int index = (bufferSize + ((end + offset) % bufferSize)) % bufferSize;
  
  return buffer[index];
}
