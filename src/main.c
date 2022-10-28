#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "token.h"
#include "label.h"
#include "trace.h"
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
    LbList LList = {0};
    
    // Parse
    if (DEBUG) {
      printf("\nPARSING\n\n");
    }

    ParserStatus parserStat = parser_start(&TList, &LList, source);

      
    if (parserStat == SYNTAX_ERR) {
      return 1;
    }

    
    Ring RingBuf = {0};
    init_ring(&RingBuf, 10);
    
    // Run
    if (DEBUG) {
      printf("\nRUNNING\n\n");
    }
    ProgramStatus progStat = run_program(&TList, &LList, &RingBuf);

    if (progStat == RUNTIME_ERR) {
      printf("\nTRACEBACK\n\n");
      print_trace(&RingBuf);
    }
    
    destroy_tokens(&TList);
    destroy_labels(&LList);
    destroy_ring(&RingBuf);
    free(source);
    

    return progStat;

  }

  return 0;
}
