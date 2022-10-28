#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "label.h"
#include "trace.h"

Trace create_trace(int fromLine, Label toLabel, int fromPtr, int previousLabel) {
  Trace trace;
  trace.fromLine = fromLine;
  trace.toName = strdup(toLabel.name);
  trace.fromPtr = fromPtr;
  trace.fromLabel = previousLabel;

  return trace;
}

void init_ring(Ring* buf, int size) {
  buf->size = size;
  buf->ringPtr = 0;
  buf->data = (Trace*) realloc(buf->data, sizeof(Trace) * buf->size);
}

void destroy_ring(Ring* buf) {
  int i;
  for (i=0; i<buf->size;i++) {
    if (buf->data[i].toName) {
      free(buf->data[i].toName);
    }
  }
  free(buf->data);
}

void append_trace(Ring* buf, Trace trace) {
  if (DEBUG) {
    printf("Appending trace %s, fromLine %i, fromPtr %i\n", trace.toName, trace.fromLine, trace.fromPtr);
  }
  buf->data[buf->ringPtr++] = trace;
  if (buf->ringPtr > buf->size) {
    buf->ringPtr = 0;
  }
}

void print_trace(Ring* buf) {
  int i;
  for (i=0; i<buf->size; i++) {
    buf->ringPtr--;

    if (buf->ringPtr < 0) {
      buf->ringPtr = buf->size-1;
    }
    Trace trace = buf->data[buf->ringPtr];
    if (trace.fromLine) {
      printf("CALL TRACEBACK %i: %s, from line %i\n", i, trace.toName, trace.fromLine);
    }
  }
}


