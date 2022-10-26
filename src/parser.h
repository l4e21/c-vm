#ifndef PARSER_H
#define PARSER_H

char* read_ascii_file(const char* path);

enum __TokenType {INST, NUMBER, REG, NUM_OF_TYPES};

typedef enum __TokenType TokenType;

enum __TokenInstruction {
  OP_PUSH,
  OP_POP,
  OP_MOV,
  OP_PRINT,
  OP_ADD_STACK,
  OP_PEEK,
  OP_HLT,
  NUM_OF_INSTRUCTIONS
};

typedef enum __TokenInstruction TokenInstruction;

struct __TOKEN {
  int data;
  int type;
  int line;
};

typedef struct __TOKEN Token;

Token* create_token(int data, int type, int line);
void destroy_token(Token* token);

struct __TOKENLIST {
  Token** data;
  int ptr;
  int size;
};

typedef struct __TOKENLIST TokenList;

void append_token(TokenList* list, Token* token);
Token* get_token(TokenList* list, int index);
void destroy_tokens(TokenList* list);

enum __Registers {A, B, C, D, E, F, IP, SP, NUM_OF_REGISTERS};

typedef enum __Registers Registers;

// Number handled by ITOA
int get_instruction(char* lex);
int get_register(char* lex);


enum __ParserStatus {
  SUCCESS,
  SYNTAX_ERR
};

typedef enum __ParserStatus ParserStatus;

ParserStatus parser_start(TokenList* list, char* source);


#endif
