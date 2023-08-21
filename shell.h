#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define CONVERT_LOWERCASE
#define CONVERT_UNSIGNED

int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: a pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *hitory;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

char *starts_with(const char *, const char *);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);

size_t print_list_str(const list_t *);
list_t *add_node_end(list_t **, const char *, int);

void _eputs(char *);

int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);

int _putchar(char c);
void _puts(char *str);
char *_strdup(const char *str);
char *_strcpy(char *dest, char *src);

#endif
