#ifndef INTERFACE_H
#define INTERFACE_H

#include <map>
#include <vector>

#define inputChar "> "

/* main run function */
int terminal();

namespace cmd_helpers
{
    /* current main command contains the current first command */
    static char* main_command;

    static char* args;

    /* execute_command is a helper to analyze a command string and execute the command */
    int execute_command(const char *command);

    /* store_alias stores an alias for later use */
    int store_alias(const char* command);

    /* cmdHelp print function usable in command line */
    int cmd_help();

    /* split_str splits a string at ' ' */
    void split_str(const char* line);

    /* aliases holds a list of all aliases */
    static std::map<char*, char*> aliases;
} // cmd_helpers


// function for autocompletion
char **command_completion(const char *, int, int);
char *command_name_generator(const char *, int);

#endif