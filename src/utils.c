#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char* read_ascii_file(const char* path) {
  FILE* fp = fopen(path, "r");

  if (!fp) {
    printf("Could not open %s", path);
    return NULL;
  }

  // Get file size
  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  // Make a buffer
  char* buf = (char*) malloc(sizeof(char) * (size));

  if (!buf) {
    printf("Could not allocate buffer for file %s\n", path);
    return NULL;
  }
  
  fread(buf, 1, size, fp);
  buf[size] = '\0';

  return buf;
}
