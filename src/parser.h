#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "label.h"

enum __Registers {A, B, C, D, E, F, IP, SP, NUM_OF_REGISTERS};

typedef enum __Registers Registers;

// Number handled by ITOA
// Sym is a string
int get_instruction(char* lex);
int get_register(char* lex);


enum __ParserStatus {
  SUCCESS,
  SYNTAX_ERR
};

typedef enum __ParserStatus ParserStatus;

ParserStatus parser_start(TokenList* list, LbList* labels, char* source);


#endif
