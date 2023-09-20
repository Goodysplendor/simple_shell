#include "shell.h"
/**
 * split_string - Splits a string into words based on delimiters.
 * @input_str: The input string to split.
 * @delimiters: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **split_string(char *input_str, char *delimiters)
{
	int i, j, k, m, num_words = 0;
	char **tokens;

	if (input_str == NULL || input_str[0] == '\0')
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (i = 0; input_str[i] != '\0'; i++)
	{
		if (!is_delim(input_str[i], delimiters) &&
				(is_delim(input_str[i + 1], delimiters) || !input_str[i + 1]))
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	tokens = malloc((1 + num_words) * sizeof(char *));
	if (!tokens)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(input_str[i], delimiters))
			i++;
		k = 0;

		while (!is_delim(input_str[i + k], delimiters) && input_str[i + k])
			k++;
		tokens[j] = malloc((k + 1) * sizeof(char));
		if (!tokens[j])
		{
			for (k = 0; k < j; k++)
				free(tokens[k]);
			free(tokens);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			tokens[j][m] = input_str[i++];
		tokens[j][m] = '\0';
	}
	tokens[j] = NULL;
	return (tokens);
}

/**
 * split_string_by_char - Splits a string
 * into words based on a single character delimiter.
 * @input_str: The input string to split.
 * @delimiter: The delimiter character.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **split_string_by_char(char *input_str, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **tokens;

	if (input_str == NULL || input_str[0] == '\0')
		return (NULL);
	for (i = 0; input_str[i] != '\0'; i++)
	{
		if ((input_str[i] != delimiter && input_str[i + 1] == delimiter)
				|| (input_str[i] != delimiter && !input_str[i + 1]) || input_str[i + 1] == delimiter)
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	tokens = malloc((1 + num_words) * sizeof(char *));

	if (!tokens)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (input_str[i] == delimiter && input_str[i] != delimiter)
			i++;
		k = 0;
		while (input_str[i + k] != delimiter && input_str[i + k] &&
				input_str[i + k] != delimiter)
			k++;
		tokens[j] = malloc((k + 1) * sizeof(char));

		if (!tokens[j])
		{
			for (k = 0; k < j; k++)
				free(tokens[k]);
			free(tokens);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			tokens[j][m]
				= input_str[i++];
		tokens[j][m] = '\0';
	}
	tokens[j] = NULL;
	return (tokens);
}
