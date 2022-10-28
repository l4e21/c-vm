#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "token.h"

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
    if (DEBUG) {
      printf("Reallocating size\n");
    }
    list->size += list->size + 1;
    list->data = (Token*) realloc(list->data, sizeof(Token) * list->size);
  }
  if (DEBUG) {
  printf("Appending %i %i %i\n", token.data, token.type, token.line);
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
