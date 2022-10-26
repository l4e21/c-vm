#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

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

int get_instruction(char* lex) {
  if (strcmp(lex, "OP_PUSH") == 0) {
    return OP_PUSH;
  } 
  if (strcmp(lex, "OP_PEEK") == 0) {
    return OP_PEEK;
  } 
  if (strcmp(lex, "OP_ADD_STACK") == 0) {
    return OP_ADD_STACK;
  } 
  if (strcmp(lex, "OP_HLT") == 0) {
    return OP_HLT;
  } 
  if (strcmp(lex, "OP_POP") == 0) {
    return OP_POP;
  } 
  if (strcmp(lex, "OP_MOV") == 0) {
    return OP_MOV;
  } 
  if (strcmp(lex, "OP_PRINT") == 0) {
    return OP_PRINT;
  } 
  else {
    return -1;
  }
}

int get_register(char* lex) {
  if (strcmp(lex, "%A") == 0) {
    return A;
  } 
  if (strcmp(lex, "%B") == 0) {
    return B;
  } 
  if (strcmp(lex, "%C") == 0) {
    return C;
  } 
  if (strcmp(lex, "%D") == 0) {
    return D;
  } 
  if (strcmp(lex, "%E") == 0) {
    return E;
  } 
  if (strcmp(lex, "%F") == 0) {
    return F;
  } 
  if (strcmp(lex, "%IP") == 0) {
    return IP;
  } 
  if (strcmp(lex, "%SP") == 0) {
    return SP;
  } 
  else {
    return -1;
  }
}

ParserStatus parser_start(TokenList* list, char* source) {
  char lex[256];  
  int i = 0;
  int lexc = 0;
  int line = 1;
  
  while (source[i] != '\0') {
    memset(lex, 0, 256);

    // Word -> Lex 
    while(source[i] != ' ' && source[i] != '\n' && source[i] != '\0') {
      lex[lexc++] = source[i++];
    }
    
    lex[lexc] = '\0';


    // Dispatch
    int numRepr = atoi(lex);

    if ((numRepr != 0) || !strcmp(lex, "0")) {
      printf("Number. %s\n", lex);
      Token* tok = create_token(numRepr, NUMBER, line);
      append_token(list, tok);
    }

    else if (lex[0] == '%') {
      printf("Register. %s\n", lex);
      int reg = get_register(lex);

      if (reg == -1) {
        printf("Syntax Error: Unrecognised Register %s\n, line %i\n", reg, line);
        return SYNTAX_ERR;
      }
      
      Token* tok = create_token(reg, REG, line);
      append_token(list, tok);
    }

    else {
      printf("Instruction. %s\n", lex);
      int instr = get_instruction(lex);

      if (instr == -1) {
        printf("Syntax Error: Unrecognised Instruction %s, line %i\n", lex, line);
        return SYNTAX_ERR;
      }

      Token* tok = create_token(instr, INST, line);
      append_token(list, tok);
      
      if (instr == OP_HLT) {
        return SUCCESS;
      }
    }
    
    // New line
    if (source[i] == '\n') {
      line++;
    }

    // Reset ready
    i++;
    lexc = 0;

  }
  return SUCCESS;

};
