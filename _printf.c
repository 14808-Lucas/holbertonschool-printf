#include "main.h"

/**
 * _printf - handles c, s, and %% conversions
 * @format: the format string
 *
 * Return: the total number of characters written
 */
int	_printf(const char *format, ...)
{
	va_list	args;
	int count;
	int i;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!format[i + 1])
			{
				va_end(args);
				return (-1);
			}
			i++;
			if (format[i] == 'c')
				count += handle_char(args);
			else if (format[i] == 's')
				count += handle_string(args);
			else if (format[i] == '%')
				count += handle_percent();
		
			else
			{
				count += putchar_out('%');
				count += putchar_out(format[i]);
			}
		}
		else
			count += putchar_out(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
