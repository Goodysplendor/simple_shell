#include "shell.h"

/**
 * my_exit - Exit the shell.
 * @info: Pointer to the info_t structure.
 *
 * Return: Exits with the given exit status, or 0 if info->argv[0] != "exit".
 */
int my_exit(info_t *info)
{
	int exit_code;

	if (info->argv[1]) /* Check for exit argument */
	{
		exit_code = _erratoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_code;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - Change the current directory of the process.
 * @info: Pointer to the info_t structure.
 *
 * Return: Always 0.
 */
int my_cd(info_t *info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure message here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - Display help information (not yet implemented).
 * @info: Pointer to the info_t structure.
 *
 * Return: Always 0.
 */
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help function is not yet implemented.\n");
	if (0)
		_puts(*arg_array); /* Temporary unused variable workaround */
	return (0);
}
