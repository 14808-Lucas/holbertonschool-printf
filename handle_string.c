#include "main.h"

/**
 * handle_string - writes a %s argument to standard output in a single
 * write() call, using the string itself as the buffer
 * @args: the variadic argument list (already positioned at the string arg)
 *
 * Return: the number of characters written, or -1 if write failed
 */
int	handle_string(va_list args)
{
	char	*str;
	int	len;

	str = va_arg(args, char *);
	if (str == NULL)
	str = "(null)";
	len = 0;
	while (str[len])
		len++;
	if (write(1, str, len) != len)
		return (-1);
	return (len);
}
