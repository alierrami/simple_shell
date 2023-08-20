#include "shell.h"
/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strlen - calculates the length of a string
 * @s: the string whose length to check
 * Return: length of the string
 */
int _strlen(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: modified dest pointer
 */
char *_strcat(char *dest, char *src)
{
	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

/**
 * _strcmp - performs lexicographic comparison of two strings
 * @s1: the first string
 * @s2: the second string
 * Return: -1 if s1 < s2
 * 	   1 if s1 > s2
 * 	   0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
