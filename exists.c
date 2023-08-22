#include "shell.h"
/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: maximum number of characters to copy
 * Return: the concatenated string
 */
char *_strncpy(char *dest, const char *src, int n)
{
	char *original_dest = dest;

	while (n > 0 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}

	while (n > 0)
	{
		*dest = '\0';
		dest++;
		n--;
	}
	return (original_dest);
}

/**
 * _strncat - concatenates two strings
 * @dest: a pointer to the destination string
 * @src: a pointer to the source string
 * @n: maximum number of characters to concatenate from the source string
 * Return: the concatenated string
 */
char *_strncat(char *dest, const char *src, int n)
{
	char *result_dest = dest;
	int i = 0, j = 0;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		des[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (result_dest);
}

/**
 * _strchr - locates a character in a string
 * @s: a pointer to the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the location of that character in the string
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	if (c == '\0')
		return (s);

	return (NULL);
}
