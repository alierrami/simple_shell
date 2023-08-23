#include "shell.h"
/**
 * _myhelp - changes the current directory of the process
 * @info: structure containing potential arguments
 * Return: always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		-puts(*arg_array);
	return (0);
}
