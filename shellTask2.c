#include "main.h"

/**
 * getPathValue - copy the value of the PATH variable of the environment
 * to a pointer passed to it
 *
 * Return: void.
 */
void getPathValue(char *pathValue)
{
	char *temp = NULL;		/* used to hold the current string in the environ */
	char **env_it;
	char *key, *value;
	int i = 0;

	env_it = environ;

	while (env_it[i] != NULL)
	{
		if (i == 6)
		{
			i++;
			continue;
		}
		temp = malloc(sizeof(char) * 500);
		strCopyWithLimit(temp, env_it[i], 250);
		key = strtok(temp, "=");

		if (strcmp(key, "PATH") == 0)
		{
			value = strtok(NULL, "=");
			copyPath(pathValue, value);
		}
		i++;
		free(temp);
		temp = NULL;
	}
}


/**
 * searchFileInPath - takes a path and a file name, then search for that file,
 * if found it, make argv[0] point to its whole path.
 * @argv: array of strings in which the first index contains the file name.
 * @path: the directory path.
 * Return: 1 if found, 0 if not, -1 if error happened with opening the dir.
 */
int searchFileInPath(char **argv, char *path)
{
	DIR *dp;
	struct dirent *entry;

	dp = opendir(path);

	if (dp == NULL)
		return (-1);

	entry = readdir(dp);

	while (entry != NULL)
	{
		if (strcmp(entry->d_name, argv[0]) == 0)
		{
			char *tempPtr = argv[0];
			argv[0] = malloc(sizeof(char) * 255);
			strcpy(argv[0], path);
			strcat(argv[0], "/");
			strcat(argv[0], tempPtr);
			closedir(dp);
			return (1);
		}
		entry = readdir(dp);
	}
	closedir(dp);
	return (0);		/* not found */
}

/**
 * searchForCommand - searches for a command (executable file) in the PATH directories
 * @argv: contains the name of the file in the first index,
 * it would get its value changed if the file was found.
 *
 * Return: 0 if the Command (file) was not found, 1 if it was found
 */
int searchForCommand(char **argv)
{
	char *pathValue, *currentPath;

	if (argv == NULL || *argv == NULL)
		return (0);

	pathValue = malloc(sizeof(char) * 1024);
	getPathValue(pathValue);
	currentPath = strtok(pathValue, ":");

	while (currentPath != NULL)
	{
		int isFound = searchFileInPath(argv, currentPath);

		if (isFound == 1)
		{
			free(pathValue);
			return (1);
		}

		currentPath = strtok(NULL, ":");
	}

	free(pathValue);
	return (0);
}



/**
 * getNumberOfWords - takes a string and,
 * returns the number of arguments (words) in it.
 * @str: the string taken as input.
 *
 * Return: an integer for the number of words (arguments).
 */
int getNumberOfWords(char *str)
{
	int i = 0, numOfWords = 0;
	int isWord = 0;

	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\n')
		{
			if (!isWord)
			{
				isWord = 1;
				numOfWords++;
			}
		}
		else
			isWord = 0;
		i++;
	}

	return (numOfWords);
}
