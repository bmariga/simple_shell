#include "shell.h"

/**
 * Check if the command is a built-in function and return a pointer to it.
 * @data: data structure
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(data_t *data))(data_t *data)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", show_env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};

	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strcmpr(data->args[0], check[i].name) == 0)
			break;
	}

	if (check[i].f != NULL)
		check[i].f(data);

	return check[i].f;
}

/**
 * Exit the program.
 * @data: data structure
 * Return: void
 */
void new_exit(data_t *data)
{
	int status;

	if (_strcmpr(data->args[0], "exit") == 0 && data->args[1] != NULL)
	{
		status = _atoi(data->args[1]);

		if (status == -1)
		{
			data->status = 2;
			print_error(data, ": Illegal number: ");
			_puts2(data->args[1]);
			_puts2("\n");
			free(data->commands);
			data->commands = NULL;
			return;
		}

		data->status = status;
	}

	free(data->buffer);
	free(data->args);
	free(data->commands);
	free_env(data->env);
	exit(data->status);
}

/**
 * Print the current environment.
 * @data: data structure
 * Return: void.
 */
void show_env(data_t *data)
{
	unsigned int i;

	for (i = 0; data->env[i]; i++)
	{
		_puts(data->env[i]);
		_puts("\n");
	}

	data->status = 0;
}

/**
 * Create a new environment variable or edit an existing variable.
 * @data: data structure
 *
 * Return: void
 */
void set_env(data_t *data)
{
	char **key;
	char *var;

	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		print_error(data, ": Incorrect number of arguments\n");
		data->status = 2;
		return;
	}

	key = find_key(data->env, data->args[1]);

	if (key == NULL)
		add_key(data);
	else
	{
		var = add_value(data->args[1], data->args[2]);

		if (var == NULL)
		{
			print_error(data, NULL);
			free(data->buffer);
			free(data->commands);
			free(data->args);
			free_env(data->env);
			exit(127);
		}

		free(*key);
		*key = var;
	}

	data->status = 0;
}

/**
 * Remove an environment variable.
 * @data: data structure
 *
 * Return: void
 */
void unset_env(data_t *data)
{
	char **key, **newenv;
	unsigned int i, j;

	if (data->args[1] == NULL)
	{
		print_error(data, ": Incorrect number of arguments\n");
		data->status = 2;
		return;
	}

	key = find_key(data->env, data->args[1]);

	if (key == NULL)
	{
		print_error(data, ": No variable to unset");
		return;
	}

	for (i = 0; data->env[i] != NULL; i++)
		;

	newenv = malloc(sizeof(char *) * i);

	if (newenv == NULL)
	{
		print_error(data, NULL);
		data->status = 127;
		new_exit(data);
	}

	for (i = 0; data->env[i] != *key; i++)
		newenv[i] = data->env[i];

	for (j = i + 1; data->env[j] != NULL; j++, i++)
		newenv[i] = data->env[j];

	newenv[i] = NULL;

	free(*key);
	free(data->env);

	data->env = newenv;
	data->status = 0;
}

