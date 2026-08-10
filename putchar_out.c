#include "main.h"

/**
 * putchar_out - writes a single character to standard output
 * @c: the character to write
 *
 * Return: 1 on success, -1 on failure
 */
int	putchar_out(char c)
{
	ssize_t	result;

	result = write(1, &c, 1);
	if (result != 1)
		return (-1);
	return (1);
}
