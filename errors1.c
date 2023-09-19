#include "shell.h"

/**
 * custom_strtoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer, or -1 on error.
 */
int custom_strtoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_custom_error - Prints a custom error message to stderr.
 * @info: Pointer to the info_t structure.
 * @error_type: String containing the specified error type.
 */
void print_custom_error(info_t *info, char *error_type)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_integer - Prints an integer to a specified file descriptor.
 * @input: The integer to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_integer(int input, int fd)
{
	int (*custom_putchar)(char) = custom_putchar;
	int i, count = 0;
	unsigned int abs_val, current;

	if (fd == STDERR_FILENO)
		custom_putchar = _eputchar;

	if (input < 0)
	{
		abs_val = -input;
		custom_putchar('-');
		count++;
	}
	else
		abs_val = input;

	current = abs_val;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_val / i)
		{
			custom_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	custom_putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_integer_to_string - Converts an integer to a string.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: The converted string.
 */
char *convert_integer_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 */
void remove_first_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
