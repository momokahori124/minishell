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
	ft_putstr_fd("Error : can not find env_name\n", 1);
	exit(0);
}

void ft_putenv(char *s)
{
	while (*s++ != '=')
		;
	ft_putstr_fd(s, 1);
}
void str_to_lower(char *line)
{
	while (*line)
	{
		*line = ft_tolower(*line);
		(line)++;
	}
}

static int		word_count(char const *s)
{
	int		cnt;

	cnt = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s && !ft_isspace(*s))
		{
			cnt++;
			while (*s && !ft_isspace(*s))
				s++;
		}
	}
	return (cnt);
}

static int		word_length(char const *s)
{
	int		i;

	i = 0;
	while (!ft_isspace(s[i]) && s[i])
		i++;
	return (i);
}

static char		**insert_word(char const *s, int wc, char **res)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (i < wc)
	{
		while (ft_isspace(*s))
			s++;
		len = word_length(s);
		if (!(res[i] = malloc(sizeof(char) * (len + 1))))
			return (ptr_2d_free((void***)&res, i));
		j = 0;
		while (j < len)
		{
			res[i][j++] = *s++;
		}
		res[i][j] = '\0';
		i++;
	}
	res[i] = NULL;
	return (res);
}

char			**ft_split_white_space(char const *s)
{
	char	**res;
	int		wc;

	if (!s)
		return (NULL);
	wc = word_count(s);
	if (!(res = malloc(sizeof(char *) * (wc + 1))))
		return (NULL);
	res = insert_word(s, wc, res);
	return (res);
}

void rm_quotaion(char **s)
{
	int len;
	int i;
	char *tmp;

	if (**s != '\'' && **s != '\"')
		return;
	len = ft_strlen(*s);
	if ((*s)[len - 1] != (*s)[0])
		return;
	char *ret = malloc(sizeof(char) * (len - 2 + 1));
	i = 0;
	while (i < (len - 2))
	{
		ret[i] = (*s)[i + 1];
		i++;
	}
	ret[i] = '\0';
	tmp = *s;
	*s = ret;
	free(tmp);
}

int is_cmd(char *line, char *cmd)
{
	char **ret = ft_split_white_space(line);
	int r;
	int i;

	i = 0;
	while (ret[i])
	{
		str_to_lower(ret[i]);
		rm_quotaion(&(ret[i]));
		i++;
	}
	r = ft_strncmp(ret[0], cmd, MAX(ft_strlen(ret[0]), ft_strlen(cmd)));
	free(ret);
	return (r);
}


void		execute_cmd(char *line, char *envp[])
{
	//ここでlineを元に、コマンドを実行して、出力する
	if (is_cmd(line, "pwd") == 0)
	{
		ft_putenv(envp[search_env(envp, "PWD")]);
		ft_putstr_fd("\n", 1);
	}
	else if (is_cmd(line, "exit") == 0)
	{
		ft_putstr_fd("Bye! exit\n", 1);
		exit(0);
	}
	else if (is_cmd(line, "env") == 0)
	{
		put_envs(envp);
	}
	else if (is_cmd(line, "help") == 0)
	{
		put_help_message();
	}
	else if (is_cmd(line, "ls") == 0)
	{
		puts("ls");

	}
	else if (*line == '\0')
		return;
	else
		put_cmd_not_found(line);
}

int		main(int argc, char *argv[], char *envp[])
{
	char	*command;

	put_welcome_message();
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	while (1)
	{
		put_prompt(envp);
		command = read_command_line();
		execute_cmd(command, envp);
	}
	(void)argc;
	(void)argv;
}
