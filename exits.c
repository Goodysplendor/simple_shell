#include "shell.h"

/**
 * custom_strncpy - Copy a string up to a specified length.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to copy.
 *
 * Return: The concatenated string.
 */
char *custom_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * custom_strncat - Concatenate two strings up to a specified length.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to concatenate.
 *
 * Return: The concatenated string.
 */
char *custom_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (result);
}

/**
 * custom_strchr - Locate a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area in s where the character is found,
 * or NULL if not found.
 */
char *custom_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
