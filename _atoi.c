#include "shell.h"
#include <unistd.h>
/**
 * check_interactive - Determine if the shell is in interactive mode.
 * @info: Pointer to the info_t structure.
 *
 * Return: 1 if interactive mode, 0 otherwise.
 */
int check_interactive(info_t *info)
{
	return (is_terminal(STDIN_FILENO) && is_standard_fd(info->readfd));
}

/**
 * is_delimiter - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if it's a delimiter, 0 otherwise.
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * is_alpha - Check if a character is an alphabetic character.
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * custom_atoi - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in the string, the converted number otherwise.
 */
int custom_atoi(char *s)
{
	int i, sign = 1, status = 0, result = 0;

	for (i = 0; s[i] != '\0' && status != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			status = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (status == 1)
			status = 2;
	}

	if (sign == -1)
		return (-result);
	else
		return (result);
}
