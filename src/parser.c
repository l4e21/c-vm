#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "parser.h"

int get_instruction(char* lex) {
  if (strcmp(lex, "PUSH") == 0) {
    return PUSH;
  } 
  if (strcmp(lex, "PEEK") == 0) {
    return PEEK;
  } 
  if (strcmp(lex, "ADD") == 0) {
    return ADD;
  } 
  if (strcmp(lex, "HLT") == 0) {
    return HLT;
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

    else {
      printf("Instruction. %s\n", lex);
      int instr = get_instruction(lex);
      Token* tok = create_token(instr, instr, line);
      append_token(list, tok);
      
      if (instr == -1) {
        printf("Syntax Error: Unrecognised Instruction %s\n", lex);
        return SYNTAX_ERR;
      }

      if (instr == HLT) {
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
