#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "interp.h"

char* registerName(int reg) {
  if (reg == A) {
    return "A";
  }
  if (reg == B) {
    return "B";
  }
  if (reg == C) {
    return "C";
  }
  if (reg == D) {
    return "D";
  }
  if (reg == E) {
    return "E";
  }
  if (reg == F) {
    return "F";
  }
  if (reg == IP) {
    return "IP";
  }
  if (reg == SP) {
    return "SP";
  }

  return "0";
}

ProgramStatus run_program(TokenList* program) {
  int r[NUM_OF_REGISTERS] = {0};
  int ip = r[IP];
  int sp = r[SP];
  int stack[STACK_LENGTH];

  int running = 1;
  
  while(running) {
    Token* currentTok = program->data[ip];
    
    if (currentTok->data == OP_PUSH) {
      Token* to = program->data[++ip];

      if (to->type == NUMBER) {
        stack[++sp] = to->data;
      }
      else if (to->type == REG) {
        stack[++sp] = r[to->data];
      }
      else {
        printf("Runtime error: Type can't be pushed: %i\n", to->type);
        return RUNTIME_ERR;
      }
    }
    else if (currentTok->data == OP_POP) {
      r[program->data[++ip]->data] = stack[sp--];
    }

    else if (currentTok->data == OP_ADD_STACK) {
      int res = stack[sp] + stack[--sp];
      stack[sp] = res;
    }
    else if (currentTok->data == OP_MOV) {
      Token* from = program->data[++ip];
      Token* to = program->data[++ip];
      if (from->type == NUMBER) {
        r[to->data] = from->data;
      }
      else if (from->type == REG) {
        r[to->data] = r[from->data];
      }
      else {
        printf("Runtime error: Type can't be mov'd: %i\n", to->type);
      }
    }    
    else if (currentTok->data == OP_HLT) {
      return PROG_SUCCESS;
    }
    else if (currentTok->data == OP_PEEK) {
      printf("Top of stack: %d\n", stack[sp]);
    }
    else if (currentTok->data == OP_PRINT) {
      Token* to_print = program->data[++ip];
      if (to_print->type == NUMBER) {
        printf("%i\n", to_print->data);
      }
      else if (to_print->type == REG) {
        printf("%s: %i\n", registerName(to_print->data), r[to_print->data]);
      }
      else {
        printf("Runtime error: Type can't be printed: %i\n", to_print->type);
      }
    }
    else {
      printf("Runtime error: Unrecognised instruction %i\n", program->data[ip]->data);
      return RUNTIME_ERR;
    }
    
    ip++;
  }

  return PROG_SUCCESS;
}
