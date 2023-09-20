#include "shell.h"
/**
 * custom_list_length - Determine the length of a linked list.
 * @list_head: Pointer to the first node.
 *
 * Return: The size of the list.
 */

size_t custom_list_length(const list_t *list_head)
{
	size_t count = 0;

	while (list_head)
	{
		list_head = list_head->next;
		count++;
	}
	return (count);
}

/**
 * custom_list_to_strings - Convert a linked list to an array of strings.
 * @list_head: Pointer to the first node.
 *
 * Return: An array of strings.
 */

char **custom_list_to_strings(list_t *list_head)
{
	list_t *node = list_head;
	size_t list_size = custom_list_length(list_head);
	char **strings;
	char *str;
	size_t i, j;

	if (!list_head || !list_size)
		return (NULL);
	strings = malloc(sizeof(char *) * (list_size + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}

/**
 * custom_print_list - Print all elements of a list_t linked list.
 * @list_head: Pointer to the first node.
 *
 * Return: The size of the list.
 */

size_t custom_print_list(const list_t *list_head)
{
	size_t count = 0;

	while (list_head)
	{
		_puts(convert_number(list_head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(list_head->str ? list_head->str : "(nil)");
		_puts("\n");
		list_head = list_head->next;
		count++;
	}
	return (count);
}

/**
 * custom_node_starts_with - Find a node whose string starts with a prefix.
 * @list_head: Pointer to the list head.
 * @prefix: The prefix to match.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL.
 */

list_t *custom_node_starts_with(list_t *list_head, char *prefix, char c)
{
	char *p = NULL;

	while (list_head)
	{
		p = starts_with(list_head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (list_head);
		list_head = list_head->next;
	}
	return (NULL);
}

/**
 * custom_get_node_index - Get the index of a node in a linked list.
 * @list_head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1.
 */

ssize_t custom_get_node_index(list_t *list_head, list_t *node)
{
	size_t index = 0;

	while (list_head)
	{
		if (list_head == node)
			return (index);
		list_head = list_head->next;
		index++;
	}
	return (-1);
}
