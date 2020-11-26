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
	while (*s++ != '=')
		;
	ft_putstr(s);
}

void		execute_cmd(char *line, char *envp[])
{
	//ここでlineを元に、コマンドを実行して、出力する
	if (ft_memcmp(line, "pwd", 3) == 0)
	{
		ft_putenv(envp[search_env(envp, "PWD")]);
		ft_putstr("\n");
	}
}

void		put_prompt(char *envp[])
{
	char *s;

	s = envp[search_env(envp, "USER")];
	ft_putenv(s);
	ft_putstr(" ❤️ > ");
}

void		perror_exit(char *s)
{
	ft_putstr(s);
	exit(0);
}

char		*read_command_line(char *envp[])
{
	char	*command;
	char	*tmp;
	char	buf;
	ssize_t	rc;

	put_prompt(envp);
	command = ft_strdup("");
	while ((rc = read(0, &buf, 1)) >= 0 && buf != '\n')
	{
		if (rc == 0)
		{
			write(0, "\033[0K", 4);
			continue ;
		}
		tmp = command;
		command = ft_strjoinch(command, buf);
		free(tmp);
	}
	if (rc == -1)
	{
		free(command);
		perror_exit("ERROR_Message");
	}
	return (command);
}

int		main(int argc, char *argv[], char *envp[])
{
	char	*command;

	ft_putstr("\n\n❤️ ❤️ ❤️ Welcome to minishell ❤️ ❤️ ❤️\n\n");
	while (1)
	{
		command = read_command_line(envp);
		execute_cmd(command, envp);
	}
	(void)argc;
	(void)argv;
}
