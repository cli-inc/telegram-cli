#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

bool quit = false;

int terminal() {
     while (!quit) {  // run until quit
        char *line = readline("> ");
        if(!line) break;  // ignore empty lines
        if(*line) add_history(line); // add line to history
        puts(line);
        if (line == "help")
          puts("helping user...");
        free(line);
      }
      return 0;
}