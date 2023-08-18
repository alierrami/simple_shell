#include "shell.h"
/**
 * print_list_str - prints only the str element of a list_t list
 * @h: a pointer to the first node
 * Return: size of the list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
