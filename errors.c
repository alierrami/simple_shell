#include "shell.h"
/**
 * _eputs - prints an input string
 * @str: the string to be printed
 * Return: nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: the character to print
 * Return: on success 1
 * on error -1 is returned and error is set appropriately
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: the character to print
 * @fd: the file descriptor to write to
 * Return: on success 1
 * 	   on error -1 is returned and error is set appropriately
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 * Return: the number of bytes written
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (str == NULL)
	{
		return (-1);
	}

	while (str[i] != '\0')
	{
		i++;
	}

	int bytes_written = write(fd, str, i);

	if (bytes_written == -1)
	{
		return (-1);
	}
	return (bytes_written);
}
