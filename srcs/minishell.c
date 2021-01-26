/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/25 16:33:44 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// char	*search_env(char **env, char *str, t_minishell_info *info)
char	*search_env(char *str, int num, t_envlst *env_lst)
{
	size_t		i;

	while (env_lst)
	{
		if ((env_lst->value)[0] == str[0] &&
				ft_strncmp(env_lst->value, str, num) == 0)
		{
			i = 0;
			while (env_lst->value[i] != '=')
				i++;
			return (env_lst->value + i + 1);
		}
		env_lst = env_lst->next;
	}
	return (NULL);
}

void ft_putenv(char *s, t_minishell_info *info)
{
	while (*s++ != '=')
		;
	if (ft_putstr_fd(s, 1) == false)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

/*
** info.current_dir_path = getcwd(NULL, 0); は
** pwdのためにカレントディレクトリを取得して構造体に入れている
** pwd ; pwdみたいな時に二回getcwd呼ぶの嫌だったのでそうした
*/

int		console_loop(t_minishell_info *info)
{
	char	*command;

	put_prompt(info);
	while (1)
	{
		if ((command = waiting_for_input(info)) == NULL)
			write(1, "\033[0K", 4); //これいらないかも、なんで書いたのか忘れた
		else
		{
			if (parse_command(info, command) != false)
				execute_command(info);
			// while (info->cmd_lst)
			// {
			// 	t_cmdlst *tmp;
			// 	tmp = info->cmd_lst->next;

			// 	free(info->cmd_lst);
			// 	info->cmd_lst = tmp;
			// }
		// 	printf("command = [%s]\n", info->command);
		// fflush(stdout);
			// ptr_free((void **)&(info->command));
		}
		// free(info->current_dir_path);
		// exit(0);
		// info->cmd_lst = NULL;
		put_prompt(info);
	}
	return (1);
}

// __attribute__((destructor))
// void end()
// {
// 	system("leaks minishell");
// }

void	set_minishell_info(t_minishell_info *info)
{
	info->current_dir_path = getcwd(NULL, 0);
	info->cmd_lst = NULL; // リスト初期化
	info->cmd_split = NULL; // リスト初期化
	info->cmd_lst_num = 0; // リスト初期化
	info->env = NULL;
	// info->command = NULL;
	// info->prev_rc = 0;
}

// static char		*get_working_dir(char *pwd)
// {
// 	int	len;
// 	int	count;

// 	len  = ft_strlen(pwd) - 1;
// 	count = 0;
// 	while (len >= 0)
// 	{
// 		if (pwd[len] == '/')
// 			count++;
// 		if (count == 2)
// 			return (pwd + len + 1);
// 		len--;
// 	}
// 	return (pwd);
// }

void	set_prompt_message(char *envp[], t_envlst *env_lst)
{
	char *s;
	(void)envp;

	s = search_env("USER", 4, env_lst);
	g_user_name = s;
	g_user_name_count = 0;
	while (g_user_name[g_user_name_count])
		g_user_name_count++;
	// s = get_working_dir(envp[search_env(envp, "PWD")]);
	s = search_env("PWD", 3, env_lst);
	g_working_dir = s;
	g_working_dir_count = 0;
	while (g_working_dir[g_working_dir_count])
		g_working_dir_count++;
}

void	shell_level_up(void)
{
	extern char	**environ;
	size_t		i;
	int			j;

	i = 0;
	while (environ[i])
	{
		if (environ[i][0] == 'S' && environ[i][1] == 'H' &&
			ft_strncmp(environ[i], "SHLVL", 5) == 0)
		{
			j = 0;
			while (environ[i][j++] != '=')
				;
			printf("%d\n", ft_atoi(environ[i] + j) + 1);
			int	current_shlvl = ft_atoi(environ[i] + j) + 1;
			int	len = ft_numlen(current_shlvl);
			environ[i][j + len] = '\0';
			while (current_shlvl != 0)
			{
				environ[i][j + len - 1] = current_shlvl % 10 + '0';
				current_shlvl /= 10;
				len--;
			}
		}
		i++;
	}
}

void	set_env(t_minishell_info *info)
{
	t_envlst	*begin;
	t_envlst	*next;
	size_t		i;
	extern char	**environ;

	if (!(begin = malloc(sizeof(t_envlst))))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	begin->value = ft_strdup(environ[0]);
	begin->next = NULL;
	info->env = begin;
	i = 1;
	while (environ[i])
	{
		if (!(next = malloc(sizeof(t_envlst))))
			all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		next->value = ft_strdup(environ[i]);
		next->next = NULL;
		begin->next = next;
		begin = next;
		i++;
	}
}

int	main()
{
	t_minishell_info	info;
	extern char			**environ;

	// put_welcome_message();
	shell_level_up();
	set_minishell_info(&info); //ここでinfoの中にenv情報入れる
	set_env(&info); //ここでinfoの中にenv情報入れる
	set_prompt_message(environ, info.env);
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	console_loop(&info);
}
