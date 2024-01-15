#include <stdio.h>
#include <unistd.h>
#include "./main.h"

/**
 * main - the main of the simple shell project
 * @argc: the number of arguments provided to the program
 * @argv: the actaul arguments provided to the program
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("Error: Wrong usage of the program.");
		printf("please only run the program wtihout passing anything else\n");
		exit(1);
	}
	shell(argv[0]);

	return (0);
}
