#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <string>

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
    cmd_helpers::split_str((char*)"Wtf?");
     while (!quit) {  // run until quit
        char *line = readline(inputChar);
        if(!line) break;  // ignore empty lines
        if(*line) add_history(line); // add line to history
        //#ifdef DEBUG    // only print debug if in debug mode compiled
        puts(line);
        //#endif
        
        int code = cmd_helpers::execute_command(line);
        if (code != 0) {
            return code;
        }
        if (quit) {
            return 0;
        }
        free(line);
      }
      return -1;
}

namespace cmd_helpers {
    int execute_command(const char *command) {
        split_str(command);
        if ((strncmp(command, "quit", 4) == 0) || (strncmp(command, "exit", 4) == 0)) {
            quit = true;
            return 0;
        } else if (strncmp(command, "help", 4) == 0) {
            return cmd_help();
        } else if (strncmp(command, "alias", 5) == 0) {
            return store_alias(command);
        }
        return 0;
    }

    int store_alias(const char* command) {

        return 0;
    }

    void split_str(const char* line) {
        bool first_space = true;
        int size = sizeof(line);

        std::string main_command_string;
        std::string args_string;
        for (int i = 0; i < strlen(line); ++i) {
            if (line[i] == ' ') {
                if (!first_space) {
                    args_string += ' ';
                }
                first_space = false;
            } else {
                if (first_space) {
                    main_command_string += line[i];
                } else {
                    args_string += line[i];
                }
            }
        }
        main_command = (char*)main_command_string.c_str();
        args = (char*)args_string.c_str();
    }

    int cmd_help() {
        printf ("%sexit/quit     quits programm%s\n", COLOR_YELLOW, COLOR_NORMAL);
        printf ("%shelp          prints this message%s\n", COLOR_YELLOW, COLOR_NORMAL);
        return 0;
    }
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
