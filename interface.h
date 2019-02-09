#ifndef INTERFACE_H
#define INTERFACE_H

#define inputChar "> "

/* main run function */
int terminal();

// function for autocompletion
char **command_completion(const char *, int, int);
char *command_name_generator(const char *, int);

#endif