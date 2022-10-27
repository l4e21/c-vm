
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

char* read_ascii_file(const char* path) {
  FILE* fp = fopen(path, "r");

  if (!fp) {
    printf("Could not open %s", path);
    return NULL;
  }

  // Get file size
  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  // Make a buffer
  char* buf = (char*) malloc(sizeof(char) * (size));

  if (!buf) {
    printf("Could not allocate buffer for file %s\n", path);
    return NULL;
  }
  
  fread(buf, 1, size, fp);
  buf[size] = '\0';

  return buf;
}

Token create_token(int data, int type, int line) {
  Token tok;
  tok.data = data;
  tok.type = type;
  tok.line = line;

  return tok;
}

void destroy_token(Token token) {
  /* free(token); */
}

void append_token(TokenList* list, Token token) {
  if (list->ptr >= list->size) {
    list->size += list->size + 1;
    list->data = (Token*) realloc(list->data, sizeof(Token) * list->size);
  }
  
  list->data[list->ptr++] = token;
  return;
}

Token get_token(TokenList* list, int index) {
  return list->data[index];
}

void destroy_tokens(TokenList* list) {
  /* for (int i=0; i<list->ptr;i++) { */
  /*   free(list->data[i]); */
  /* } */

  free(list->data);
}

int get_instruction(char* lex) {
  if (strcmp(lex, "OP_PUSH") == 0) {
    return OP_PUSH;
  } 
  /* if (strcmp(lex, "OP_LBL") == 0) { */
  /*   return OP_LBL; */
  /* }  */
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


Label create_label(int progPtr, char* name) {
  Label lbl;
  
  lbl.progPtr = progPtr;
  lbl.name = name;

  return lbl;
}

void destroy_label(Label label) {
  /* free(label); */
}

void append_label(LbList* list, Label label) {
  if (list->ptr >= list->size) {
    list->size += list->size + 1;
    list->data = (Label*) realloc(list->data, sizeof(Label) * list->size);
  }
  
  list->data[list->ptr++] = label;
  return;
}

Label get_label(LbList* list, int index) {
  return list->data[index];
}

int find_label_by_name(LbList* list, char* name) {
  int i;

  for (i=0; i<list->ptr; i++) {
    Label lbl = list->data[i];
    if (strcmp(lbl.name, name) == 0) {
      return i;
    }
  };
  return -1;
}

void destroy_labels(LbList* list) {
  /* for (int i=0; i<list->ptr;i++) { */
  /*   /\* free(&list->data[i]); *\/ */
  /* } */

  free(list->data);
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

      printf("Number. %s %i\n", lex, line);
      Token tok;
      tok = create_token(numRepr, NUMBER, line);
      append_token(list, tok);
    }

    else if (lex[0] == '_') {
      printf("Label. %s %i\n", lex, line);
      
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
      printf("Register. %s %i\n", lex, line);
      int reg = get_register(lex);

      if (reg == -1) {
        printf("Syntax Error: Unrecognised Register %s\n, line %i\n", lex, line);
        return SYNTAX_ERR;
      }
      
      Token tok;
      tok = create_token(reg, REG, line);
      append_token(list, tok);
    }

    else {
      printf("Instruction. %s %i\n", lex, line);
      int instr = get_instruction(lex);

      if (instr == -1) {
        printf("Syntax Error: Unrecognised Instruction %s, line %i\n", lex, line);
        return SYNTAX_ERR;
      }

      Token tok;
      tok = create_token(instr, INST, line);
      append_token(list, tok);
      
      if (instr == OP_HLT) {
        printf("Number of commands: %i\n", commandNum);
        return SUCCESS;
      }
    }
    
    // New line
    if (source[i] == '\n') {
      line++;
    }

    // Reset ready
    i++;
    commandNum++;
    lexc = 0;
  }

  printf("Number of commands: %i\n", commandNum);
  return SUCCESS;

};
