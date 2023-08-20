#include "shell.h"
/**
 * _memset - fills a block of memory with a specified value
 * @s: a pointer to the start of the memory block to fill
 * @b: the value to set each byte of the memory block to
 * @n: the number of bytes to set
 * Return: a pointer to the satrt of the filled memory block
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 * Return: void
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
