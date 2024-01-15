#include "main.h"

/**
 * getNumberOfWords - takes a string an returns the number of arguments (words) in it.
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
		if (!isWord && str[i] != ' ' && str[i] != '\n')
		{
			isWord = 1;
			numOfWords++;
		}
		else
			isWord = 0;
		i++;
	}

	return (numOfWords);
}
