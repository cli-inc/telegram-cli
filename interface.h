#ifndef INTERFACE_H
#define INTERFACE_H

#define inputChar "> "

/* main run function */
int terminal();

#pragma region cmd_helpers
/* cmdHelp print function usable in command line */
int cmdHelp();
#pragma endregion cmd_helpers

// function for autocompletion
char **command_completion(const char *, int, int);
char *command_name_generator(const char *, int);

#endif