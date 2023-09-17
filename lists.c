#include "shell.h"
/**
 * custom_add_node - Add a node to the start of the linked list.
 * @list_head: Address of the pointer to the list's head.
 * @data: The data for the new node.
 * @index: The index of the new node used for tracking history.
 *
 * Return: A pointer to the new node.
 */

list_t *custom_add_node(list_t **list_head, const char *data, int index)
{
	list_t *new_entry;

	if (!list_head)
		return (NULL);
	new_entry = malloc(sizeof(list_t));
	if (!new_entry)
		return (NULL);
	_memset((void *)new_entry, 0, sizeof(list_t));
	new_entry->num = index;
	if (data)
	{
		new_entry->str = _strdup(data);
		if (!new_entry->str)
		{
			free(new_entry);
			return (NULL);
		}
	}
	new_entry->next = *list_head;
	*list_head = new_entry;
	return (new_entry);
}
/**
 * custom_add_node_end - Add a node to the end of the linked list.
 * @list_head: Address of the pointer to the list's head.
 * @data: The data for the new node.
 * @index: The index of the new node used for tracking history.
 *
 * Return: A pointer to the new node.
 */

list_t *custom_add_node_end(list_t **list_head, const char *data, int index)
{
	list_t *new_node, *current_node;

	if (!list_head)
		return (NULL);
	current_node = *list_head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = index;
	if (data)
	{
		new_node->str = _strdup(data);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
	{
		*list_head = new_node;
	}
	return (new_node);
}
/**
 * custom_print_list_data - Print only the data element of a linked list.
 * @list_head: Pointer to the first node of the list.
 *
 * Return: The size of the list.
 */

size_t custom_print_list_data(const list_t *list_head)
{
	size_t list_size = 0;

	while (list_head)
	{
		_puts(list_head->str ? list_head->str : "(nil)");
		_puts("\n");
		list_head = list_head->next;
		list_size++;
	}
	return (list_size);
}
/**
 * custom_delete_node_at_index - Delete a node at the specified index.
 * @list_head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */

int custom_delete_node_at_index(list_t **list_head, unsigned int index)
{
	list_t *current_node, *previous_node;
	unsigned int node_index = 0;

	if (!list_head || !*list_head)
		return (0);
	if (!index)
	{
		current_node = *list_head;
		*list_head = (*list_head)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *list_head;
	while (current_node)
	{
		if (node_index == index)
		{
			previous_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		node_index++;
		previous_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}
/**
 * custom_free_list - Free all nodes of the linked list.
 * @list_head_ptr: Address of pointer to the list's head.
 *
 * Return: void.
 */

void custom_free_list(list_t **list_head_ptr)
{
	list_t *current_node, *next_node, *list_head;

	if (!list_head_ptr || !*list_head_ptr)
		return;
	list_head = *list_head_ptr;
	current_node = list_head;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	*list_head_ptr = NULL;
}
