#include "shell.h"
/**
 * string_copy - Copies a string.
 * @destination: The destination.
 * @source: The source.
 *
 * Return: Pointer to the destination.
 */

char *string_copy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == NULL)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
	return (destination);
}

/**
 * string_duplicate - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */

char *string_duplicate(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	duplicate = malloc(sizeof(char) * (length + 1));

	if (!duplicate)
		return (NULL);
	for (length++; length--;)
		duplicate[length] = *--str;
	return (duplicate);
}

/**
 * string_print - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */

void string_print(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * character_print - Writes the character to stdout.
 * @character: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int character_print(char character)
{
	static int buffer_index;
	static char write_buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(1, write_buffer, buffer_index);
		buffer_index = 0;
	}
	if (character != BUF_FLUSH)
		write_buffer[buffer_index++] = character;
	return (1);
}
