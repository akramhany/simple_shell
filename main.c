#include <stdio.h>
#include <unistd.h>
#include "./main.h"

/**
 * main - the main of the simple shell project
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("Error: Wrong usage of the program, please only run the program wtihout passing anything else");
		exit(1);
	}
	shell(argv[0]);
	return (0);
}
