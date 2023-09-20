#include "shell.h"
/**
 * _fill_memory - Fills a memory area with a constant byte.
 * @mem: Pointer to the memory area.
 * @byte: The byte value to fill the memory with.
 * @size: The size (in bytes) of the memory area to be filled.
 *
 * Return: A pointer to the filled memory area.
 */

char *_fill_memory(char *mem, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		mem[i] = byte;
	return (mem);
}

/**
 * free_string_array - Frees an array of strings and the array itself.
 * @str_array: The array of strings to free.
 */

void free_string_array(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temp);
}

/**
 * _realloc_memory - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: The byte size of the previous block.
 * @new_size: The byte size of the new block.
 *
 * Return: Pointer to the reallocated memory block.
 */

void *_realloc_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
