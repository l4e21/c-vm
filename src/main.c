#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "interp.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Not enough args!\n");
    return 1;
  }

  if (strcmp(argv[1], "compile") == 0) {
    // Read
    char* source = read_ascii_file(argv[2]);

    TokenList TList = {0};

    // Parse
    ParserStatus parserStat = parser_start(&TList, source);
    
    if (parserStat == SYNTAX_ERR) {
      return 1;
    }
    
    // Run
    ProgramStatus progStat = run_program(&TList);
    
    destroy_tokens(&TList);
    free(source);

    return progStat;

  }

  return 0;
}
