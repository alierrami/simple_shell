#include "shell.h"

/**
 * _add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
_list_t *_add_node(_list_t **head, const char *str, int num)
{
	_list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(_list_t));
	if (!new_head)
		return (NULL);
	_mem_set((void *)new_head, 0, sizeof(_list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _str_dup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * _add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
_list_t *_add_node_end(_list_t **head, const char *str, int num)
{
	_list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(_list_t));
	if (!new_node)
		return (NULL);
	_mem_set((void *)new_node, 0, sizeof(_list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _str_dup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * _print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t _print_list_str(const _list_t *h)
{
	size_t i = 0;

	while (h)
	{
		__puts(h->str ? h->str : "(nil)");
		__puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int _delete_node_at_index(_list_t **head, unsigned int index)
{
	_list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * _free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void _free_list(_list_t **head_ptr)
{
	_list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
