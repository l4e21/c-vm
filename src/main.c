#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "lex.h"
#include "parser.h"
#include "vm.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Not enough args!\n");
    return 1;
  }

  if (strcmp(argv[1], "compile") == 0) {
    // Read
    char* source = read_ascii_file(argv[2]);

    TokenList TList = {0};

    // Lex
    ParserStatus parserStat = parser_start(&TList, source);
    
    if (parserStat == SYNTAX_ERR) {
      return 1;
    }


    // Compile
    int program[TList.ptr];

    for (int i=0; i<TList.ptr; i++) {
      Token* tok = get_token(&TList, i);
      program[i] = tok->data;
    }
  

    // Run
    ProgramStatus progStat = run_program(program);
    
  /*   if (progStat == RUNTIME_ERR) { */
  /*     return 1; */
  /*   } */

  /*   destroy_tokens(&TList); */
  /*   free(source); */
  }

  return 0;
}
