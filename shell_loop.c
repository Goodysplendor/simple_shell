#include "shell.h"
/**
 * shell_loop - Main shell loop.
 * @info: The parameter and return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or an error code.
 */

int shell_loop(info_t *info, char **av)
{
	ssize_t read_status = 0;
	int builtin_result = 0;
	int error_number;
	int (*function)(info_t *info);

	while (read_status != -1 && builtin_result != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_status = get_input(info);
		if (read_status != -1)
		{
			set_info(info, av);
			builtin_result = find_builtin(info);
			if (builtin_result == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->error_number == -1)
			exit(info->status);
		exit(info->error_number);
	}
	return (builtin_result);
}

/**
 * find_builtin_command - Finds and executes a builtin command.
 * @info: The parameter and return info struct.
 *
 * Return: -1 if builtin command not found,
 *         0 if builtin command executed successfully,
 *         1 if builtin command found but not successful,
 *         2 if builtin command signals exit().
 */

int find_builtin_command(info_t *info)
{
	int i, builtin_result = -1;

	builtin_table builtins[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (i = 0; builtins[i].name; i++)
	{
		if (_strcmp(info->argv[0], builtins[i].name) == 0)
		{
			info->line_count++;
			builtin_result = builtins[i].function(info);
			break;
		}
	}
	return (builtin_result);
}

/**
 * find_external_command - Finds an external command in PATH.
 * @info: The parameter and return info struct.
 *
 * Return: void
 */

void find_external_command(info_t *info)
{
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	int arg_count = count_non_empty_args(info->arg);

	if (arg_count == 0)
		return;
	path = find_command_in_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		find_external_command(info);
	}
	else
	{
		if ((interactive(info)
					|| _getenv(info, "PATH=") || info->
					argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			find_external_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_external_command - Forks an exec thread to run an external command.
 * @info: The parameter and return info struct.
 *
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
