#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void shell(char *programName);
char *getCommand(ssize_t *n, char **inputLine);
int checkOnlySpaces(char *line);

extern char **environ;

#endif
