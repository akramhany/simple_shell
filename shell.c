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
char *getCommand(ssize_t *n, char **inputLine)
{
	char *line = NULL;
	size_t bufferSize = 0;

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
		*inputLine = line;
		line = strtok(line, "\n ");
	}


	return (line);
}

/**
 * shell - simple shell program
 * @programName: the name of the program
 * RETURN: void
 */
void shell(char *programName)
{
	char *argv[2];
	char *inputLine = NULL;
	const char *const shellName = "#cisfun$";
	int status = 0, instructionNumber = 0;
	ssize_t n = 0;
	pid_t pid = 1;

	argv[0] = NULL;
	argv[1] = NULL;

	do {
		if (isatty(STDIN_FILENO) == 1)
			printf("%s ", shellName);

		argv[0] = getCommand(&n, &inputLine);
		instructionNumber++;

		pid = fork();

		if (inputLine != NULL && pid != 0)
		{
			free(inputLine);
			inputLine = NULL;
			argv[0] = NULL;
		}

	} while (pid != 0 && (wait(&status) != -1));

	if (pid == 0 && argv[0] != NULL)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			if (errno == ENOENT)
			{
				printf("%s: %d: %s: No such file or directory\n", programName, instructionNumber, argv[0]);
				free(inputLine);
				exit(1);
			}
			else if (errno == EACCES)
			{
				printf("%s: %d: %s: Permission denied\n", programName, instructionNumber, argv[0]);
				free(inputLine);
				exit(126);	
			}
		}
	}
}
