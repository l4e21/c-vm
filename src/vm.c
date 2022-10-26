#include <stdlib.h>
#include <stdio.h>
#include "lex.h"
#include "vm.h"

/* char* registerName(int reg) { */
/*   if (reg == A) { */
/*     return 'A'; */
/*   } */
/*   if (reg == B) { */
/*     return 'B'; */
/*   } */
/*   if (reg == C) { */
/*     return 'C'; */
/*   } */
/*   if (reg == D) { */
/*     return 'D'; */
/*   } */
/*   if (reg == E) { */
/*     return 'E'; */
/*   } */
/*   if (reg == F) { */
/*     return 'F'; */
/*   } */
/*   if (reg == IP) { */
/*     return 'I'; */
/*   } */
/*   if (reg == SP) { */
/*     return 'S'; */
/*   } */

ProgramStatus run_program(int* program) {
  int r[NUM_OF_REGISTERS] = {0};
  int ip = r[IP];
  int sp = r[SP];
  int stack[STACK_LENGTH];

  int running = 1;
  
  while(running) {

    if (program[ip] == PUSH) {
      stack[sp++] = program[++ip];
    }
    else if (program[ip] == PEEK) {
      printf("Top of stack: %d\n", stack[sp-1]);
    }
    else if (program[ip] == ADD) {
      int res = stack[--sp] + stack[--sp];
      stack[sp] = res;
      sp++;
    }
    else if (program[ip] == HLT) {
      return PROG_SUCCESS;
    }
    else {
      printf("Unrecognised instruction %i\n", program[ip]);
      return RUNTIME_ERR;
    }
    
    ip++;
  }

  return PROG_SUCCESS;
}
