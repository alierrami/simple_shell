#include "shell.h"

/**
 * _my_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _my_env(_info_t *info)
{
	_print_list_str(info->env);
	return (0);
}

/**
 * _get_env - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_get_env(_info_t *info, const char *name)
{
	_list_t *node = info->env;
	char *p;

	while (node)
	{
		p = __starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _my_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _my_setenv(_info_t *info)
{
	if (info->argc != 3)
	{
		_e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _my_unsetenv(_info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_e_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unset_env(info, info->argv[i]);

	return (0);
}

/**
 * _populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _populate_env_list(_info_t *info)
{
	_list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
