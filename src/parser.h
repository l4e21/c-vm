#ifndef PARSER_H
#define PARSER_H

#include "lex.h"

enum __ParserStatus {
  SUCCESS,
  SYNTAX_ERR
};

typedef enum __ParserStatus ParserStatus;

ParserStatus parser_start(TokenList* list, char* source);


#endif
