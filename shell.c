#include "./main.h"

/**
 * getCommand - take input command from stdin and return it
 *
 * Return: a string
 */
char *getCommand(void)
{
	char *line = NULL;
	size_t n = 0;

	if (getline(&line, &n, stdin) == -1 || *line == EOF)
	{
		free(line);
		exit(-1);
	}

	line = strtok(line, "\n");

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
	const char *const shellName = "#cisfun$";
	int status = 0;
	pid_t pid;

	argv[0] = NULL;
	argv[1] = NULL;

	do {
		printf("%s ", shellName);

		if (argv[0] != NULL)
		{
			free(argv[0]);
			argv[0] = NULL;
		}

		argv[0] = getCommand();
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