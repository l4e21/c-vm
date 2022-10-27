#ifndef PARSER_H
#define PARSER_H

char* read_ascii_file(const char* path);

enum __TokenType {INST, NUMBER, REG, SYM, NUM_OF_TYPES};

typedef enum __TokenType TokenType;

enum __TokenInstruction {
  OP_PUSH,
  OP_POP,
  OP_MOV,
  OP_JMP,
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

Token create_token(int data, int type, int line);
void destroy_token(Token token);

struct __TOKENLIST {
  Token* data;
  int ptr;
  int size;
};

typedef struct __TOKENLIST TokenList;

void append_token(TokenList* list, Token token);
Token get_token(TokenList* list, int index);
void destroy_tokens(TokenList* list);


struct __Label {
  int progPtr;
  char* name;
};

typedef struct __Label Label;

Label create_label(int progPtr, char* name);
void destroy_label(Label label);

struct __LBLIST {
  Label* data;
  int ptr;
  int size;
};

typedef struct __LBLIST LbList;

void append_label(LbList* list, Label label);
Label get_label(LbList* list, int index);
int find_label_by_name(LbList* list, char* name);
void destroy_labels(LbList* list);


enum __Registers {A, B, C, D, E, F, IP, SP, NUM_OF_REGISTERS};

typedef enum __Registers Registers;

// Number handled by ITOA
char* get_sym(char* lex);
int get_instruction(char* lex);
int get_register(char* lex);


enum __ParserStatus {
  SUCCESS,
  SYNTAX_ERR
};

typedef enum __ParserStatus ParserStatus;

ParserStatus parser_start(TokenList* list, LbList* labels, char* source);


#endif
