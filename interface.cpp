#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <string>

#include "interface.h"
#include "colors.h"
#include "options.h"

bool quit = false;

char *commands[] = {
    (char*)"help",
    (char*)"quit",
    (char*)"exit",
    (char*)"alias",
    NULL
};

int terminal() {
    rl_attempted_completion_function = command_completion;
     while (!quit) {  // run until quit
        char *line = readline(inputChar);
        if(!line) break;  // ignore empty lines
        if(*line) add_history(line); // add line to history
        //#ifdef DEBUG    // only print debug if in debug mode compiled
        //puts(line);
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
        if (options::verbose == false) {
            puts("non verbose");
        }
        split_str(command, main_command, arguments);
        if (options::verbose) {
            printf("executing: %s\n", main_command);
        }
        if ((strncmp(main_command, "quit", 4) == 0) || (strncmp(command, "exit", 4) == 0)) {
            quit = true;
            return 0;
        } else if (strncmp(main_command, "help", 4) == 0) {
            return cmd_help();
        } else if (strncmp(main_command, "alias", 5) == 0) {
            return store_alias(arguments);
        }
        return 0;
    }

    int store_alias(const char* command) {
        puts ("storing alias");
        aliases.insert(std::pair<char*, char*>("msg", "test"));
        aliases.insert(std::pair<char*, char*>("test", "test"));
        aliases.insert(std::pair<char*, char*>("hello", "test"));
        return 0;
    }

    void split_str(const char* line, char *&main, char *&args) {
        std::string in (line);
        std::string main_command_string, args_string;
        std::string::size_type pos;
        pos = in.find(' ', 0);
        if (pos == std::string::npos) { // checking if space was found
            //puts("no space found");
            main = (char*)line;
            return;
        }
        args_string = in.substr(pos+1); // spliting spring
        main_command_string = in.substr(0,pos);
        //printf("main_command_string: %s, pos: %d\n", main_command_string.c_str(), pos);
        main = (char*)main_command_string.c_str();  // writing into variables
        args = (char*)args_string.c_str();
    }

    int cmd_help() {
        printf ("%sexit/quit                 exit programm%s\n", COLOR_YELLOW, COLOR_NORMAL);
        printf ("%salias %s<name> <command>%s    stores %s<command>%s under %s<name>%s\n", COLOR_YELLOW, COLOR_LIGHT_GREEN, COLOR_YELLOW, COLOR_LIGHT_GREEN, COLOR_YELLOW, COLOR_LIGHT_GREEN, COLOR_NORMAL);
        printf ("%shelp                      prints this message%s\n", COLOR_YELLOW, COLOR_NORMAL);
        return 0;
    }
}

char **command_completion(const char *text, int start, int end) {
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, command_name_generator);
}

char *command_name_generator(const char *text, int state) {
    static int list_index, map_index, len;
    char *command;

    if (!state) {
        list_index = 0;
        map_index = 0;
        len = strlen(text);
    }

    // go over hard coded command list
    while(command = commands[list_index++]) {
        if (strncmp(command, text, len) == 0) {
            return strdup(command);
        }
    }
    
    // go over alias map
    std::map<char*, char*>::iterator it = cmd_helpers::aliases.begin();
    for (int i = 0; i < map_index; i++) {
        it++;
    }
    for (;it != cmd_helpers::aliases.end(); ++it) {
        map_index++;
        if (strncmp(it->first, text, len) == 0) {
            return strdup((char*)it->first);
        }
    }

    return NULL;
}
