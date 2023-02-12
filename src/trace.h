#ifndef TRACE_H
#define TRACE_H

#include "token.h"


// Call trace
struct __TRACE {
  int fromLine; 
  int toLine;
  int fromPtr;
  char* toName;
  int fromLabel;
};

typedef struct __TRACE Trace;

struct __RING {
  int ringPtr;
  int size;
  Trace* data; // Info on a particular jump trace
};

typedef struct __RING Ring;

// On an error, we need to print the contents of the ring buffer

Trace create_trace(int fromLine, int toLine, Label toLabel, int fromPtr, int previousLabel);
void init_ring(Ring* buf, int size);
void destroy_ring(Ring* buf);
void append_trace(Ring* buf, Trace trace);
void print_trace(Ring* buf);


#endif

