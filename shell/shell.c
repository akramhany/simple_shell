#include "../main.h"

/**
 * printEnv - prints the environ variable
 *
 * Return: void
 */
void printEnv(void)
{	
	int i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * checkOnlySpaces - takes a string, check if it consists of spaces only or not
 * @line: the string to check (given in char * form)
 *
 * Return: 1 if yes, 0 if no.
 */
int checkOnlySpaces(char *line)
{
	int i = 0;

	if (line == NULL)
		return (0);

	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}

	return (1);
}

/**
 * getCommand - take input command from stdin and return it
 * @n: the size of the input line getting from stdin
 * @inputLine: pointer to the inputLine to free it after finishing execution
 *
 * Return: an array of strings, each string is a word in the input.
 */
char **getCommand(ssize_t *n, char **inputLine)
{
	char *line = NULL, *token = NULL;
	size_t bufferSize = 0;
	char **argv = NULL;
	int argvSize = 0, i = 0;

	/* reads input from stdin, getline will allocate space for line if it is not allocated. */
	*n = getline(&line, &bufferSize, stdin);

	if (*n == -1 || *line == EOF)
	{
		free(line);
		exit(0);
	}

	/* check if the given input is only spaces or endlines. */
	if (checkOnlySpaces(line) == 1)
	{
		/* if yes, free the allocated memory in line, and set inputLine to NULL */
		free(line);
		line = NULL;
		*inputLine = NULL;
	}
	else
	{
		/* get number of words seperated by a space from the input. */
		argvSize = getNumberOfWords(line);
		
		/* allocate memory for the array of strings, the last index should be NULL. */
		argv = malloc(sizeof(char *) * (argvSize + 1));
		
		/* store line in the *inputLine, to free it in shell. */
		*inputLine = line;

		/* divide the line into words based on if an end line or a space exist between them. */
		while ((token = strtok(line, "\n ")) != NULL)
		{
			argv[i++] = token;
			line = NULL;
		}

		/* make the last index in argv NULL. */
		argv[argvSize] = NULL;
	}

	return (argv);
}


/**
 * executeCommand - executes a command then check and handle errors
 * @argv: the array of strings containing the command
 * @programName: the name of the program, which would be printed in the error message.
 * @instructionNumber: the current command number to print in the error message
 *
 * Return: 1 means it executed without errors, 0 means it encountered an error
 */
int executeCommand(char **argv, char *programName,
		   int instructionNumber)
{
	if (execve(argv[0], argv, environ) == -1)
	{
		if (errno == ENOENT)
		{
			printf("%s: %d: %s: No such file or directory\n",
				programName, instructionNumber, argv[0]);
			return (1);
		}
		else if (errno == EACCES)
		{
			printf("%s: %d: %s: Permission denied\n",
				programName, instructionNumber, argv[0]);
			return (126);
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
	int status = 0, instructionNumber = 0, notAbsPath = 0;
	ssize_t n = 0;
	pid_t pid = 1;

	do {
		/* reset notAbsPath to zero */
		notAbsPath = 0;

		/* check if the program is open in terminal (interactive mode) or not (non-interactive mode) */
		if (isatty(STDIN_FILENO) == 1)
			printf("%s ", shellName);

		/* get the all the input words as an array of strings. */
		argv = getCommand(&n, &inputLine);

		instructionNumber++;

		/* check if the command is to exit. */
		if (argv && strcmp(argv[0], "exit") == 0)
		{
			free(inputLine);
			free(argv);
			status = WEXITSTATUS(status);
			exit(status);
		}
		else if (argv && strcmp(argv[0], "env") == 0)	/* if command is env, print the env variable. */
		{
			printEnv();
		}

		/* check if the command is the program name or absPath & if it exists or not. */
		if (argv != NULL && (*argv[0] == '/' || *argv[0] == '.'))
		{
			pid = fork();
		}
		else if (searchForCommand(argv) == 1)
		{
			pid = fork();
			notAbsPath = 1;
		}
		else if (argv != NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				programName, instructionNumber, argv[0]);
		}

		/* free the allocated inputLine and argv for the parent process. */
		if (inputLine != NULL && pid != 0)
		{
			free(inputLine);
			inputLine = NULL;
			if (notAbsPath && argv[0])
			{
				free(argv[0]);
				argv[0] = NULL;
			}
			free(argv);
			argv = NULL;
		}

	} while (pid != 0 && wait(&status));	/* keep looping for the parent process. */

	if (pid == 0 && argv != NULL)
	{
		/* if the execution failed, store the status code to exit with it. */
		int statusCode = executeCommand(argv, programName, instructionNumber);

		/* free the allocated memory for the child process. */
		free(inputLine);
		if (notAbsPath && argv[0])
		{
			free(argv[0]);
			argv[0] = NULL;
		}
		free(argv);
		exit (statusCode);
	}
}
