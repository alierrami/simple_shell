#include "shell.h"
/**
 * _putchar - writes the character to stdout
 * @c: the character to print
 * Return: on success 1
 * 	   on error -1 is returned and error is set appropriately
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 * Return: nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: a pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *new_str;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;
	new_str = malloc(sizeof(char) * (length + 1));
	if (new_str == NULL)
		return (NULL);
	for (length++; length--;)
		new_str[length] = *--str;
	return (new_str);
}

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: a pointer to the destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
