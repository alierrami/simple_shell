#include "shell.h"

/**
 * _is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _is_chain(_info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * _check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void _check_chain(_info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * _replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_alias(_info_t *info)
{
	int i;
	_list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _str_chr(node->str, '=');
		if (!p)
			return (0);
		p = _str_dup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * _replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_vars(_info_t *info)
{
	int i = 0;
	_list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_str_cmp(info->argv[i], "$?"))
		{
			_replace_string(&(info->argv[i]),
				_str_dup(_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_str_cmp(info->argv[i], "$$"))
		{
			_replace_string(&(info->argv[i]),
				_str_dup(_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = _node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			_replace_string(&(info->argv[i]),
				_str_dup(_str_chr(node->str, '=') + 1));
			continue;
		}
		_replace_string(&info->argv[i], _str_dup(""));

	}
	return (0);
}

/**
 * _replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
