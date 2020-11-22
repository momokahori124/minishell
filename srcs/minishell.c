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

int		main(int argc, char *argv[], char *envp[], char *apple[])
{
	put_envs(envp);

}

