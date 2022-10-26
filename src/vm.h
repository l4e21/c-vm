#ifndef VM_H
#define VM_H

#include "lex.h"

#define STACK_LENGTH 100

enum __Registers {A, B, C, D, E, F, IP, SP, NUM_OF_REGISTERS};

typedef enum __Registers Registers;

enum __ProgramStatus {
  PROG_SUCCESS,
  RUNTIME_ERR
};

typedef enum __ProgramStatus ProgramStatus;

int registerName(int reg);

ProgramStatus run_program(TokenList* program);

void push();
void add();
void peek();


#endif
