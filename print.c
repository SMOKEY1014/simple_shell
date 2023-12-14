#include "main.h"
/**
 * _print - prints an output to the screen.
 * @format: takes the required format of string.
 */


void _print(const char *format, ...)
{
	char buffer[1024];
	va_list args;

	va_start(args, format);

	vsnprintf(buffer, sizeof(buffer), format, args);

	write(1, buffer, strlen(buffer));

	va_end(args);
}
