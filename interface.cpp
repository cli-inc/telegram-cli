#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "interface.h"

bool quit = false;

char *commands[] = {
    "help",
    "quit",
    "depp",
    NULL
};

int terminal() {
    rl_attempted_completion_function = command_completion;
     while (!quit) {  // run until quit
        char *line = readline(inputChar);
        if(!line) break;  // ignore empty lines
        if(*line) add_history(line); // add line to history
        puts(line);
        if (strcmp(line, "help") == 0)
          puts("helping user...");
        free(line);
      }
      return 0;
}

char **command_completion(const char *text, int start, int end) {
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, command_name_generator);
}

char *command_name_generator(const char *text, int state) {
    static int list_index, len;
    char *command;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while(command = commands[list_index++]) {
        if (strncmp(command, text, len) == 0) {
            return strdup(command);
        }
    }
    return NULL;
}
