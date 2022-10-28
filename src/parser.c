#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "parser.h"
#include "token.h"


int get_instruction(char* lex) {
  if (strcmp(lex, "OP_PUSH") == 0) {
    return OP_PUSH;
  } 
  if (strcmp(lex, "OP_RET") == 0) {
    return OP_RET;
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
  if (strcmp(lex, "OP_JMP") == 0) {
    return OP_JMP;
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


ParserStatus parser_start(TokenList* list, LbList* labels, char* source) {
  char lex[256];  
  int i = 0;
  int lexc = 0;
  int line = 1;
  Label lbl;
  int commandNum = 0;
  /* list->size += 1; */
  /* labels->size += 1; */
  
  while (source[i] != '\0') {
        // New line
    if (source[i] == '\n') {
      line++;
      i++;
    }

    else if (source[i] == ' ') {
      i++;
    }
    
    else {
      
      // Word -> Lex
      while(source[i] != ' ' && source[i] != '\n' && source[i] != '\0') {
        lex[lexc++] = source[i++];
      }
      
      lex[lexc] = '\0';
      
      // Dispatch
      int numRepr = atoi(lex);
      /* printf("%s\n", lex); */
      /* printf("Label being parsed: %s\n", get_label(labels, 0)); */
      
      
      if ((numRepr != 0) || !strcmp(lex, "0")) {
        if (DEBUG) {
          printf("Number. %s %i\n", lex, line);
        }
        Token tok;
        tok = create_token(numRepr, NUMBER, line);
        append_token(list, tok);
      }
      
      else if (lex[0] == '_') {
        if (DEBUG) {
          printf("Label. %s %i\n", lex, line);
        }
        
        int labelPtr = find_label_by_name(labels, lex);
        
        if (labelPtr == -1) {
          Label lbl;
          lbl = create_label(commandNum, lex);
          append_label(labels, lbl);
          
          Token tok;
          tok = create_token(labels->ptr-1, SYM, line);
          append_token(list, tok);
        }
        else {
          Token tok;
          tok = create_token(labelPtr, SYM, line);
        append_token(list, tok);
        }
      }
      
      else if (lex[0] == '%') {
        if (DEBUG) {
          printf("Register. %s %i\n", lex, line);
        }
        int reg = get_register(lex);
        
        if (reg == -1) {
          printf("SYNTAX ERROR: Unrecognised Register %s\n, line %i\n", lex, line);
        return SYNTAX_ERR;
        }
        
        Token tok;
        tok = create_token(reg, REG, line);
        append_token(list, tok);
      }
      
      else {
        if (DEBUG) {
          printf("Instruction. %s %i\n", lex, line);
        }
      int instr = get_instruction(lex);
      
      if (instr == -1) {
        printf("SYNTAX ERROR: Unrecognised Instruction %s, line %i\n", lex, line);
        return SYNTAX_ERR;
      }
      
      Token tok;
      tok = create_token(instr, INST, line);
      append_token(list, tok);
      
      if (instr == OP_HLT) {
        if (DEBUG) {
          printf("Number of commands: %i\n", commandNum);
        }
        return SUCCESS;
      }
      };
      // There was a command
      commandNum++;
      lexc = 0;
    };    
  };

  if (DEBUG) {
    printf("Number of commands: %i\n", commandNum);
  }
  return SUCCESS;
};
