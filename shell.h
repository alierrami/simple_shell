#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct list_str - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} _list_t;

/**
 *struct pass_info - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct pass_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	_list_t *env;
	_list_t *history;
	_list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} _info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct _builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct _builtin
{
	char *type;
	int (*func)(_info_t *);
} _builtin_table;


/* _toem_shloop.c */
int _hsh(_info_t *, char **);
int _find_builtin(_info_t *);
void _find_cmd(_info_t *);
void _fork_cmd(_info_t *);

/* _toem_parser.c */
int _is_cmd(_info_t *, char *);
char *_dup_chars(char *, int, int);
char *__find_path(_info_t *, char *, char *);

/* loop_hsh.c */
int _loop_hsh(char **);

/* _toem_errors.c */
void _e_puts(char *);
int _e_put_char(char);
int _put_fd(char c, int fd);
int _puts_fd(char *str, int fd);

/* _toem_string.c */
int _str_len(char *);
int _str_cmp(char *, char *);
char *__starts_with(const char *, const char *);
char *_str_cat(char *, char *);

/* _toem_string1.c */
char *_str_cpy(char *, char *);
char *_str_dup(const char *);
void __puts(char *);
int _putchar(char);

/* _toem_exits.c */
char *_strn_cpy(char *, char *, int);
char *_strn_cat(char *, char *, int);
char *_str_chr(char *, char);

/* _toem_tokenizer.c */
char **str_tow(char *, char *);
char **str_tow2(char *, char);

/* _toem_realloc.c */
char *_mem_set(char *, char, unsigned int);
void f_free(char **);
void *__realloc(void *, unsigned int, unsigned int);

/* _toem_memory.c */
int _bfree(void **);

/* _toem_atoi.c */
int inter_active(_info_t *);
int _is_delim(char, char *);
int _is_alpha(int);
int __atoi(char *);

/* _toem_errors1.c */
int _err_atoi(char *);
void _print_error(_info_t *, char *);
int _print_d(int, int);
char *_convert_number(long int, int, int);
void _remove_comments(char *);

/* _toem_builtin.c */
int _my_exit(_info_t *);
int _my_cd(_info_t *);
int _my_help(_info_t *);

/* _toem_builtin1.c */
int _my_history(_info_t *);
int _my_alias(_info_t *);

/* _toem_getline.c */
ssize_t get_input(_info_t *);
int _get_line(_info_t *, char **, size_t *);
void sigint_Handler(int);

/* _toem_getinfo.c */
void _clear_info(_info_t *);
void _set_info(_info_t *, char **);
void _free_info(_info_t *, int);

/* _toem_environ.c */
char *_get_env(_info_t *, const char *);
int _my_env(_info_t *);
int _my_setenv(_info_t *);
int _my_unsetenv(_info_t *);
int _populate_env_list(_info_t *);

/* _toem_getenv.c */
char **_get_environ(_info_t *);
int _unset_env(_info_t *, char *);
int _set_env(_info_t *, char *, char *);

/* _toem_history.c */
char *_get_history_file(_info_t *info);
int _write_history(_info_t *info);
int _read_history(_info_t *info);
int _build_history_list(_info_t *info, char *buf, int linecount);
int _renumber_history(_info_t *info);

/* _toem_lists.c */
_list_t *_add_node(_list_t **, const char *, int);
_list_t *_add_node_end(_list_t **, const char *, int);
size_t _print_list_str(const _list_t *);
int _delete_node_at_index(_list_t **, unsigned int);
void _free_list(_list_t **);

/* _toem_lists1.c */
size_t _list_len(const _list_t *);
char **_list_to_strings(_list_t *);
size_t _print_list(const _list_t *);
_list_t *_node_starts_with(_list_t *, char *, char);
ssize_t _get_node_index(_list_t *, _list_t *);

/* _toem_vars.c */
int _is_chain(_info_t *, char *, size_t *);
void _check_chain(_info_t *, char *, size_t *, size_t, size_t);
int _replace_alias(_info_t *);
int _replace_vars(_info_t *);
int _replace_string(char **, char *);

#endif
