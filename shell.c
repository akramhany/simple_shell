#include "./main.h"


/**
 * checkOnlySpaces - takes a string and check if it contains only spaces or not
 * @line: the string to check (given in char * form)
 *
 * Return: bool to indicate if the string contains only spaces or not
 */
int checkOnlySpaces(char *line)
{
	int i = 0;

	if (line == NULL)
		return 0;


	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n')
			return 0;
		i++;
	}

	return 1;
}

/**
 * getCommand - take input command from stdin and return it
 *
 * Return: a string
 */
char **getCommand(ssize_t *n, char **inputLine)
{
	char *line = NULL, *token = NULL;
	size_t bufferSize = 0;
	char **argv = NULL;
	int argvSize = 0, i = 0;

	if ((*n = getline(&line, &bufferSize, stdin)) == -1 || *line == EOF)
	{
		free(line);
		exit(0);
	}

	if (checkOnlySpaces(line) == 1)
	{
		free(line);
		line = NULL;
		*inputLine = NULL;
	}
	else
	{
		argvSize = getNumberOfWords(line);
		argv = malloc(sizeof(char *) * (argvSize + 1));
		*inputLine = line;
		while ((token = strtok(line, "\n ")) != NULL)
		{
			argv[i++] = token;
			line = NULL;
		}
		argv[argvSize] = NULL;
	}

	return (argv);
}


/**
 * executeCommand - executes a command then check and handle errors
 * @argv: the array of strings containing the command
 * @inputLine: a buffer that needs to be freed before exiting
 * @programName: the name of the program
 * @instructionNumber: the current command number to print in the error message
 *
 * Return: 1 means it executed without errors, 0 means it encountered an error
 */
int executeCommand(char **argv, char *inputLine, char *programName, int instructionNumber)
{
	if (execve(argv[0], argv, environ) == -1)
	{
		if (errno == ENOENT)
		{
			printf("%s: %d: %s: No such file or directory\n", programName, instructionNumber, argv[0]);
			free(inputLine);
			free(argv);
			exit(1);
		}
		else if (errno == EACCES)
		{
			printf("%s: %d: %s: Permission denied\n", programName, instructionNumber, argv[0]);
			free(inputLine);
			free(argv);
			exit(126);	
		}
	}

	/* if the program didn't terminate it means that it encountered a problem */
	return (0);
}

/**
 * shell - simple shell program
 * @programName: the name of the program
 *
 * Return: void
 */
void shell(char *programName)
{
	char **argv = NULL;
	char *inputLine = NULL;
	const char *const shellName = "#cisfun$";
	int status = 0, instructionNumber = 0;
	ssize_t n = 0;
	pid_t pid = 1;


	do {
		if (isatty(STDIN_FILENO) == 1)
			printf("%s ", shellName);

		argv = getCommand(&n, &inputLine);
		instructionNumber++;

		pid = fork();
		if (inputLine != NULL && pid != 0)
		{
			free(inputLine);
			inputLine = NULL;
			free(argv);
			argv = NULL;
		}

	} while (pid != 0 && (wait(&status) != -1));

	if (pid == 0 && argv != NULL)
	{
		executeCommand(argv, inputLine, programName, instructionNumber);
	}
}
