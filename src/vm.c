#include <stdlib.h>
#include <stdio.h>
#include "lex.h"
#include "vm.h"

/* char* registerName(int reg) { */
/*   if (reg == A) { */
/*     return "A"; */
/*   } */
/*   if (reg == B) { */
/*     return "B"; */
/*   } */
/*   if (reg == C) { */
/*     return "C"; */
/*   } */
/*   if (reg == D) { */
/*     return "D"; */
/*   } */
/*   if (reg == E) { */
/*     return "E"; */
/*   } */
/*   if (reg == F) { */
/*     return "F"; */
/*   } */
/*   if (reg == IP) { */
/*     return "IP"; */
/*   } */
/*   if (reg == SP) { */
/*     return "SP"; */
/*   } */

ProgramStatus run_program(TokenList* program) {
  int r[NUM_OF_REGISTERS] = {0};
  int ip = r[IP];
  int sp = r[SP];
  int stack[STACK_LENGTH];

  int running = 1;
  
  while(running) {

    if (program->data[ip]->data == PUSH) {
      stack[sp++] = program->data[++ip]->data;
    }
    else if (program->data[ip]->data == PEEK) {
      printf("Top of stack: %d\n", stack[sp-1]);
    }
    else if (program->data[ip]->data == ADD) {
      int res = stack[--sp] + stack[--sp];
      stack[sp] = res;
      sp++;
    }
    else if (program->data[ip]->data == HLT) {
      return PROG_SUCCESS;
    }
    else {
      printf("Unrecognised instruction %i\n", program->data[ip]->data);
      return RUNTIME_ERR;
    }
    
    ip++;
  }

  return PROG_SUCCESS;
}
