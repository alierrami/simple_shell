#include "shell.h"

/**
 * _get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **_get_environ(_info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = _list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unset_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unset_env(_info_t *info, char *var)
{
	_list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = __starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = _delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _set_env(_info_t *info, char *var, char *value)
{
	char *buf = NULL;
	_list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_str_len(var) + _str_len(value) + 2);
	if (!buf)
		return (1);
	_str_cpy(buf, var);
	_str_cat(buf, "=");
	_str_cat(buf, value);
	node = info->env;
	while (node)
	{
		p = __starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
