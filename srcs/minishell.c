#include "../includes/minishell.h"

void	put_envs(char *envp[])
{
	int i = 0;
	while (1)
	{
		if (envp[i] == NULL)
			break;
		printf("%s\n", envp[i]);
		i++;
	}
}

void		console_loop(char *envp[])
{
	char *line;

	// ft_putstr("> ");
	while (get_next_line(0, &line) > 0)
	{
		printf("%s\n", line);
	}
	(void)envp;
}

int		main(int argc, char *argv[], char *envp[])
{
	console_loop(envp);
	// put_envs(envp);
	// (void)envp;
	(void)argc;
	(void)argv;
}

