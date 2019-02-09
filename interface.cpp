#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "interface.h"
#include "colors.h"

bool quit = false;

char *commands[] = {
    (char*)"help",
    (char*)"quit",
    (char*)"exit",
    NULL
};

int terminal() {
    rl_attempted_completion_function = command_completion;
     while (!quit) {  // run until quit
        char *line = readline(inputChar);
        int code;    // stores exit code of underlying function
        if(!line) break;  // ignore empty lines
        if(*line) add_history(line); // add line to history
        #ifdef DEBUG    // only print debug if in debug mode compiled
        puts(line);
        #endif
        if ((strncmp(line, "quit", 4) == 0) || (strncmp(line, "exit", 4) == 0)) {
            return 0;
        } else if (strncmp(line, "help", 4) == 0) {
            code = cmdHelp();
        }
        
        if (code != 0) {
            return code;
        }
        free(line);
      }
      return -1;
}

#pragma region cmd_helpers
int cmdHelp() {
    printf ("%sexit/quit     quits programm%s\n", COLOR_YELLOW, COLOR_NORMAL);
    printf ("%shelp          prints this message%s\n", COLOR_YELLOW, COLOR_NORMAL);
    return 0;
}

#pragma endregion cmd_helpers

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
