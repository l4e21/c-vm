#ifndef INTERP_H
#define INTERP_H

#include "parser.h"

#define STACK_LENGTH 100

enum __ProgramStatus {
  PROG_SUCCESS,
  RUNTIME_ERR
};

typedef enum __ProgramStatus ProgramStatus;

char* registerName(int reg);

ProgramStatus run_program(TokenList* program);

#endif
