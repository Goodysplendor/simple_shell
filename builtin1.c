#include "shell.h"

/**
 * display_history - Display the command history with line numbers.
 * @info: Pointer to the info_t structure.
 *
 * Return: Always 0.
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_shell_alias - Unset a shell alias.
 * @info: Pointer to the info_t structure.
 * @alias_str: The alias string to unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_shell_alias(info_t *info, char *alias_str)
{
	char *equal_sign, original_char;
	int result;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);

	original_char = *equal_sign;
	*equal_sign = '\0';

	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));

	*equal_sign = original_char;
	return (result);
}

/**
 * set_shell_alias - Set a shell alias.
 * @info: Pointer to the info_t structure.
 * @alias_str: The alias string to set.
 *
 * Return: 0 on success, 1 on error.
 */
int set_shell_alias(info_t *info, char *alias_str)
{
	char *equal_sign;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);

	if (!*++equal_sign)
		return (unset_shell_alias(info, alias_str));

	unset_shell_alias(info, alias_str);

	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_shell_alias - Print a shell alias.
 * @node: The alias node to print.
 *
 * Return: 0 on success, 1 on error.
 */
int print_shell_alias(list_t *node)
{
	char *equal_sign = NULL, *alias = NULL;

	if (node)
	{
		equal_sign = _strchr(node->str, '=');
		for (alias = node->str; alias <= equal_sign; alias++)
			_putchar(*alias);

		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - Manage shell aliases, similar to the 'alias' built-in.
 * @info: Pointer to the info_t structure.
 *
 * Return: Always 0.
 */
int shell_alias(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_shell_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
			set_shell_alias(info, info->argv[i]);
		else
			print_shell_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
