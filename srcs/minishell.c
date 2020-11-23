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

int			search_env(char *envp[], char *env_name)
{
	// search_env(envp, "PWD") ってやったらPWDのenv番号を出してくれる関数
	int i = 0;
	while (1)
	{
		if (envp[i] == NULL)
			break;
		if (ft_strncmp(envp[i], env_name, ft_strlen(env_name)) == 0)
			return (i);
		i++;
	}
	ft_putstr("Error : can not find env_name\n");
	exit(0);
}

void		ft_putenv(char *s)
{
	while (*s != '=')
		s++;
	s++;
	ft_putstr(s);
	ft_putstr("\n");
}

void		execute_cmd(char *line, char *envp[])
{
	//ここでlineを元に、コマンドを実行して、出力する
	if (ft_memcmp(line, "pwd", 3) == 0)
	{
		ft_putenv(envp[search_env(envp, "PWD")]);
	}
}

void		console_loop(char *envp[])
{
	char *line;

	ft_putstr("❤️ ");
	while (get_next_line(0, &line) > 0)
	{
		execute_cmd(line, envp);//コマンドを実行する
		free(line);
		ft_putstr("❤️ ");
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	console_loop(envp);
	(void)argc;
	(void)argv;
}

