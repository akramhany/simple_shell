#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

void shell(char *programName);
char **getCommand(ssize_t *n, char **inputLine);
int checkOnlySpaces(char *line);
int executeCommand(char **argv, char *programName,
		   int instructionNumber);
int getNumberOfWords(char *str);
int searchFileInPath(char **argv, char *path);
void getPathValue(char *pathValue);
int searchForCommand(char **argv);
void copyPath(char *pathValue, char *value);
void strCopyWithLimit(char *dest, char *src, int maxSize);
void printEnv(void);

extern char **environ;

#endif
