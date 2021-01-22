/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/23 02:02:47 by tjinichi         ###   ########.fr       */
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
char	*search_env(char **env, char *str)
{
	size_t	i;
	size_t	j;
	// char	*export_value;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
		{
			j = 0;
			while (env[i][j] != '=')
				j++;
			return (env[i] + j + 1);
		}
		i++;
	}
	// export_value = info->
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

int		console_loop(t_minishell_info *info, char *envp[])
{
	(void)envp;
	put_prompt(info);
	while (1)
	{
		if (read_command_line(info) == false)
			write(1, "\033[0K", 4); //これいらないかも、なんで書いたのか忘れた
		else
		{
			// if (parse_command_line(info, envp) == false)
			// 	continue ; //pwd | で次|を押してプロンプトが二つ出るのを防いでる
			if (parse_command_line(info) != false)
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

void	set_env_info(t_minishell_info *info)
{
	info->current_dir_path = getcwd(NULL, 0);
	info->cmd_lst = NULL; // リスト初期化
	info->cmd_split = NULL; // リスト初期化
	info->cmd_lst_num = 0; // リスト初期化
	info->my_env = NULL;
	info->command = NULL;
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

void	set_prompt_message(char *envp[])
{
	char *s;

	s = search_env(envp, "USER");
	g_user_name = s;
	g_user_name_count = 0;
	while (g_user_name[g_user_name_count])
		g_user_name_count++;
	// s = get_working_dir(envp[search_env(envp, "PWD")]);
	s = search_env(envp, "PWD");
	g_working_dir = s;
	g_working_dir_count = 0;
	while (g_working_dir[g_working_dir_count])
		g_working_dir_count++;
}

// void	set_env()

int		main(int argc, char *argv[])
{
	t_minishell_info	info;
	extern char			**environ;

	if (argc != 1)
	{
		red_error();
		ft_putendl_fd("Usage : ./minishell", 2);
		return (1);
	}
	// put_welcome_message();
	set_prompt_message(environ);
	info.shell_level = search_env(environ, "SHLVL");
	int i = 0;
	while (i < 1)
	{
		info.shell_level[i] = ft_atoi(info.shell_level) + 1 + '0';
		i++;
	}
	info.shell_level[i] = '\0';
	// info.shell_level[0] += ft_atoi(info.shell_level) + 1 - '0';
	printf("shell L : %s\n",info.shell_level);
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	set_env_info(&info); //ここでinfoの中にenv情報入れる
	console_loop(&info, environ);
	(void)argc;
	(void)argv;
}
