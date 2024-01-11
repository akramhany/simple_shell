#include <unistd.h>
#include "./main.h"
#include <errno.h>



/**
 * shell - simple shell program
 * @programName: the name of the program
 * RETURN: void
 */
void shell(char *programName)
{
	char **argv = {NULL, NULL};
	const char *const shellName = "#cisfun$ ";
	int n = 0, status = 0;
	pid_t pid;

	do {
		printf(shellName);

		if (argv[0] != NULL)
		{
			free(argv[0]);
			argv[0] = NULL;
		}

		argv[0] = getCommand();
		pid = fork();

	} while (pid != 0 && (wait(&status) != -1))

	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			if (errno == ENOENT)
				printf("%s: No such file or directory\n", programName);
		}
	}
}
