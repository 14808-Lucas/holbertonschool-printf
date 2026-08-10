#ifndef MAIN_H
# define MAIN_H

# include <stdarg.h>
# include <unistd.h>

int	_printf(const char *format, ...);

int	putchar_out(char c);
int	handle_char(va_list args);
int	handle_string(va_list args);
int	handle_percent(void);

#endif

