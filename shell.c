#include "./main.h"

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
		if (*n == -1)
			exit(-1);
		exit(0);
	}
	*inputLine = line;
	line = strtok(line, "\n ");

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
	int status = 0;
	ssize_t n = 0;
	pid_t pid;

	argv[0] = NULL;
	argv[1] = NULL;

	do {
		if (isatty(STDIN_FILENO) == 1)
			printf("%s ", shellName);

		if (argv[0] != NULL)
		{
			free(inputLine);
			inputLine = NULL;
			argv[0] = NULL;
		}

		argv[0] = getCommand(&n, &inputLine);
		pid = fork();

	} while (pid != 0 && (wait(&status) != -1));

	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			if (errno == ENOENT)
				printf("%s: No such file or directory\n", programName);
		}
	}
}
