#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

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

Token create_token(int data, int type, int line) {
  Token tok;
  tok.data = data;
  tok.type = type;
  tok.line = line;

  return tok;
}

void destroy_token(Token token) {
  /* free(token); */
}

void append_token(TokenList* list, Token token) {
  if (list->ptr >= list->size) {
    list->size += list->size + 1;
    list->data = (Token*) realloc(list->data, sizeof(Token) * list->size);
  }
  
  list->data[list->ptr++] = token;
  return;
}

Token get_token(TokenList* list, int index) {
  return list->data[index];
}

void destroy_tokens(TokenList* list) {
  /* for (int i=0; i<list->ptr;i++) { */
  /*   free(list->data[i]); */
  /* } */

  free(list->data);
  list->size = 0;
  list->ptr = 0;
}
