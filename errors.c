#include "shell.h"

/**
 * print_error_message - Print an error message to stderr.
 * @message: The error message to print.
 *
 * Return: Nothing.
 */
void print_error_message(char *message)
{
	int i = 0;

	if (!message)
		return;
	while (message[i] != '\0')
	{
		_eputchar(message[i]);
		i++;
	}
}

/**
 * _eputchar - Write a character to the standard error (stderr).
 * @c: The character to write.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_to_custom_fd - Write a character to a custom file descriptor.
 * @c: The character to write.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_to_custom_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * print_to_custom_fd - Print a string to a custom file descriptor.
 * @str: The string to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int print_to_custom_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_to_custom_fd(*str++, fd);
	}
	return (i);
}
