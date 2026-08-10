#include "main.h"

/**
 * handle_char - writes a %c argument to standard output
 * @args: the variadic argument list (already positioned at the char arg)
 *
 * Return: 1 on success, -1 on write failure
 */
int	handle_char(va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	return (putchar_out(c));
}
