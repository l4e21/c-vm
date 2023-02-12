#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "token.h"
#include "label.h"
#include "trace.h"
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

ProgramStatus run_program(TokenList* program, LbList* labels, Ring* tracebuf) {
  int r[NUM_OF_REGISTERS] = {0};
  int ip = r[IP];
  int sp = r[SP];
  int stack[STACK_LENGTH];
  int inLabel;

  int running = 1;

  int main = find_label_by_name(labels, "_main");
  
  if (main) {
    ip = get_label(labels, main).progPtr + 1;
    inLabel = main;
  }
  else {
    // I don't know if this should be in runtime or parsing
    printf("RUNTIME ERROR: No entrypoint found\n");
    return RUNTIME_ERR;
  }
  
  while(running) {
    Token currentTok = program->data[ip];

    if (DEBUG) {
    printf("TOKEN\nVal %i\nType %i\nLine %i\n", currentTok.data, currentTok.type, currentTok.line);
      }

    if (currentTok.type == SYM) {
      // Pass
    }

    else if (currentTok.type == NUMBER) {
      printf("RUNTIME ERROR: Stray integer %i\n", currentTok.data);
      return RUNTIME_ERR;
    }
    
    else if (currentTok.data == OP_PUSH) {
      Token to = program->data[++ip];

      if (to.type == NUMBER) {
        stack[++sp] = to.data;
      }
      else if (to.type == REG) {
        stack[++sp] = r[to.data];
      }
      else {
        printf("RUNTIME ERROR: Type can't be pushed: %i\n", to.type);
        return RUNTIME_ERR;
      }
    }
    else if (currentTok.data == OP_POP) {
      Token to_pop = program->data[++ip];
      if (to_pop.type == REG) {
        r[to_pop.data] = stack[sp--];
      }
      else {
        printf("RUNTIME ERROR: Type can't be popped: %i\n", to_pop.type);
        return RUNTIME_ERR;
      }
    }
    
    else if (currentTok.data == OP_ADD_STACK) {
      int res = stack[sp] + stack[--sp];
      stack[sp] = res;
    }
    else if (currentTok.data == OP_MOV) {
      Token from = program->data[++ip];
      Token to = program->data[++ip];
      if (from.type == NUMBER) {        
        r[to.data] = from.data;
      }
      else if (from.type == REG) {
        r[to.data] = r[from.data];
      }
      else {
        printf("RUNTIME ERROR: Type can't be mov'd: %i\n", to.type);
        return RUNTIME_ERR;
      }
    }    
    else if (currentTok.data == OP_HLT) {
      return PROG_SUCCESS;
    }
    else if (currentTok.data == OP_PEEK) {
      printf("Top of stack: %d\n", stack[sp]);
    }
    else if (currentTok.data == OP_PRINT) {
      Token to_print = program->data[++ip];
      if (to_print.type == NUMBER) {
        printf("%i\n", to_print.data);
      }
      else if (to_print.type == REG) {
        printf("%s: %i\n", registerName(to_print.data), r[to_print.data]);
      }
      else {
        printf("RUNTIME ERROR: Type can't be printed: %i\n", to_print.type);
        return RUNTIME_ERR;
      }
    }


    else if (currentTok.data == OP_JMP) {
      Token to_jmp = program->data[++ip];
            
      if (to_jmp.type == SYM) {
        Label label = get_label(labels, to_jmp.data);

        Trace trace;
        trace = create_trace(currentTok.line, label.progPtr+1, label, ip, inLabel);
        append_trace(tracebuf, trace);
        ip = label.progPtr;
        inLabel = to_jmp.data;

        // TODO
      }
      
      else {
        printf("RUNTIME ERROR: Can't jump to: %i, line %i, type %i\n", to_jmp.type, to_jmp.line, to_jmp.type);
      }
    }

    else if (currentTok.data == OP_RET) {
      Trace recentTrace = tracebuf->data[tracebuf->ringPtr-1];

      Trace returnTrace;
      returnTrace = create_trace(currentTok.line, recentTrace.fromPtr-1, get_label(labels, recentTrace.fromLabel), ip, inLabel);
      append_trace(tracebuf, returnTrace);
      ip = recentTrace.fromPtr;
      inLabel = recentTrace.fromLabel;
                           
      // Adding a trace on return as well
      /* Trace trace; */
      /* trace = create_trace(currentTok, recent */
    }
    
    else {
      printf("RUNTIME ERROR: Unrecognised instruction %i\n", program->data[ip].data);
      return RUNTIME_ERR;
    }
    
    ip++;
  }

  return PROG_SUCCESS;
}
