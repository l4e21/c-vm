#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

Token* create_token(int data, int type, int line) {
  Token* tok = (Token* ) malloc(sizeof(Token));
  tok->data = data;
  tok->type = type;
  tok->line = line;

  return tok;
}

void destroy_token(Token* token) {
  free(token);
}

void append_token(TokenList* list, Token* token) {
  if (list->ptr >= list->size) {
    list->size += list->size + 1;
    list->data = (Token**) realloc(list->data, sizeof(Token**) * list->size);
  }
  
  list->data[list->ptr++] = token;
  return;
}

Token* get_token(TokenList* list, int index) {
  return list->data[index];
}

void destroy_tokens(TokenList* list) {
  for (int i=0; i<list->ptr;i++) {
    free(list->data[i]);
  }

  free(list->data);
}
