#include "main.h"

/**
 * copyPath - takes 2 strings one of them has the path value of the environment,
 * and copies this value into the other string.
 * @pathValue: the destination string.
 * @value: the source string (contains the path value).
 * Return: void.
 */ 
void copyPath(char *pathValue, char *value)
{
	int i = 0;

	if (!pathValue || !value)
	       return;

	while (value[i] != '\0' && value[i] != ' ')
	{
		pathValue[i] = value[i];
		i++;
	}

	pathValue[i] = '\0';	
}

/**
 * strCopyWithLimit - copy from src string to dest without exceeding a certain limit.
 * @dest: destination string to copy to.
 * @src: source string to copy from.
 * maxSize: the max limit to not to exceed.
 * Return: void.
 */
void strCopyWithLimit(char *dest, char *src, int maxSize)
{
	int i = 0;

	if (!dest || !src)
		return;

	while (i < maxSize && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
}
