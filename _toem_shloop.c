#include "shell.h"

/**
 * _hsh - main shell loop
 * @inf: the parameter & return info struct
 * @avr: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int _hsh(_info_t *inf, char **avr)
{
	ssize_t re = 0;
	int builtin_rets = 0;

	while (re != -1 && builtin_rets != -2)
	{
		_clear_info(inf);
		if (inter_active(inf))
			__puts("$ ");
		_e_put_char(BUF_FLUSH);
		re = get_input(inf);
		if (re != -1)
		{
			_set_info(inf, avr);
			builtin_rets = _find_builtin(inf);
			if (builtin_rets == -1)
				_find_cmd(inf);
		}
		else if (inter_active(inf))
			_putchar('\n');
		_free_info(inf, 0);
	}
	_write_history(inf);
	_free_info(inf, 1);
	if (!inter_active(inf) && inf->status)
		exit(inf->status);
	if (builtin_rets == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_rets);
}

/**
 * _find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int _find_builtin(_info_t *info)
{
	int i, built_in_ret = -1;
	_builtin_table builtintbl[] = {
		{"exit", _my_exit},
		{"env", _my_env},
		{"help", _my_help},
		{"history", _my_history},
		{"setenv", _my_setenv},
		{"unsetenv", _my_unsetenv},
		{"cd", _my_cd},
		{"alias", _my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_str_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * _find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _find_cmd(_info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!_is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = __find_path(info, _get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_fork_cmd(info);
	}
	else
	{
		if ((inter_active(info) || _get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && _is_cmd(info, info->argv[0]))
			_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_print_error(info, "not found\n");
		}
	}
}

/**
 * _fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _fork_cmd(_info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, _get_environ(info)) == -1)
		{
			_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_print_error(info, "Permission denied\n");
		}
	}
}
