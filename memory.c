#include "shell.h"
/**
 * free_and_null - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free and set to NULL.
 *
 * Return: 1 if freed, otherwise 0.
 */

int free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
