#ifndef LEX_H
#define LEX_H

enum __TokenType {INST, NUMBER};

typedef enum __TokenType TokenType;

enum __TokenInstruction {
  PUSH,
  ADD,
  PEEK,
  HLT,
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

#endif
