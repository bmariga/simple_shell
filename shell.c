#include "shell.h"

/**
 * _EOF - handles the End of File
 * @len: return value of getline function
 * @buff: buffer
 */
void _EOF(int len, __attribute__((unused))char *buff)
{
<<<<<<< HEAD
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buff);
		}
		exit(0);
	}
}

/**
 * _isatty - verif if is interactive
 */
void _isatty(void)
{
	if (isatty(STDIN_FILENO))
		printf("$ ");
}

/**
 * sig_handler - checks if Ctrl C is pressed
 * @sig_num: int
 */
void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
		_puts("\n$ ");
}

/**
 * main - Shell
 * Return: 0 on success
 */
int main(void)
{
	int bytes_read = 0; /*Declarations*/
	char *string = NULL, *value = NULL, *pathname = NULL, **arv = NULL;
	size_t size = 0;
	list_path *head = '\0';
	void (*f)(char **) = NULL; /* Declare the store of the func*/

	signal(SIGINT, sig_handler); /*Signal be sure tat the user press the ctrl+c*/
	while (1) /*Starting the infinitive loop*/
	{
		_isatty(); /*Check if the input is interative or not interative*/
		fflush(stdin);
		bytes_read = getline(&string, &size, stdin); /*Read the line from user*/
		_EOF(bytes_read, string); /*If an error occured the program finish*/
		arv = splitstring(string, " \n"); /*Split the string into an array*/
		if (arv[0])
		{
			value = _getenv("PATH"); /*Obtain the value from the environment variable*/
			head = linkpath(value); /*Create an linked list of the path directories*/
			pathname = _which(arv[0], head); /*Search if the command exits in paths*/
			free_list(head); /*Free the linked list*/
			f = checkbuild(arv); /*Check if the command is an buildin*/
			if (f) /*If the command is an buildin free the input*/
			{
				f(arv); /*from user and run the buildin*/
			}
			if (pathname) /*If the _which find the executable in the paths, */
			{					/*free the space in memory of the command*/
				free(arv[0]);	/*and replace with the path to an success executation*/
				arv[0] = pathname;
			}
			execute(arv);
		}
		else
			freearv(arv);
	}
	free_list(head);
	freearv(arv);
	free(string);
	return (0);
=======
    char *prompt = ". $ ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;

    /* declaring void variables */
    (void)ac;

    /* Create a loop for the shell's prompt */
    while (1)
    {
        printf("%s", prompt);
        nchars_read = getline(&lineptr, &n, stdin);
        /* check if the getline function failed or reached EOF or user use CTRL + D */
        if (nchars_read == -1)
        {
            printf("Exiting shell....\n");
            return (-1);
        }

        /* allocate space for a copy of the lineptr */
        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy == NULL)
        {
            perror("tsh: memory allocation error");
            return (-1);
        }
        /* copy lineptr to lineptr_copy */
        strcpy(lineptr_copy, lineptr);

        /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(lineptr, delim);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        /* execute the command */
        execmd(argv);
    }

    /* free up allocated memory */
    free(lineptr_copy);
    free(lineptr);

    return (0);
>>>>>>> f96cd6529c1755d984b30fc176c7cf296ab489cb
}
