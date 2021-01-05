/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/06 06:51:43 by tjinichi         ###   ########.fr       */
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

/*
** info.current_dir_path = getcwd(NULL, 0); は
** pwdのためにカレントディレクトリを取得して構造体に入れている
** pwd ; pwdみたいな時に二回getcwd呼ぶの嫌だったのでそうした
*/

int		console_loop(t_minishell_info *info, char *envp[])
{
	put_prompt(envp);
	while (1)
	{
	// 	printf("command = [%s]\n", info->command);
	// fflush(stdout);
		read_command_line(info);
	// 		printf("i = [%d]\n", i);
	// fflush(stdout);
	printf("prev_rc = %d\n", info->prev_rc);
	fflush(stdout);

		if (info->prev_rc != 2000 && info->command[0] == '\0')
		{
			ptr_free((void **)&(info->command));
			// printf("[%s]\n", info->command);
			// fflush(stdout);
			write(1, "\033[0K", 4);
			put_prompt(envp);
			// printf("innnnnnnnnnn\n");
			// fflush(stdout);
			continue ;
		}
		else if (info->prev_rc == 2000)
		{
			info->prev_rc = 0;
			continue ;
		}
		// else if (info->command[0] == '\n')
		// {
		// 	ptr_free((void **)&(info->command));
		// 	// printf("[%s]\n", info->command);
		// 	// fflush(stdout);
		// 	write(1, "\033[0K", 4);
		// 	// put_prompt(envp);
		// 	// printf("innnnnnnnnnn\n");
		// 	// fflush(stdout);
		// 	// continue ;
		// }
		else
		{
			// puts("======");
			bool ppp;
			if ((ppp = parse_command_line(info, envp)) != false)
				execute_command(info);
			while (info->cmd_lst)
			{
				t_cmdlst *tmp;
				tmp = info->cmd_lst->next;
				free(info->cmd_lst);
				info->cmd_lst = tmp;
			}
		// 	printf("command = [%s]\n", info->command);
		// fflush(stdout);
			ptr_free((void **)&(info->command));
			if (ppp == false)
				continue ;
		}
		// free(info->current_dir_path);
		// exit(0);
		put_prompt(envp);
	}
	return (1);
}

// __attribute__((destructor))
// void end()
// {
// 	system("leaks minishell");
// }

void	set_env_info(t_minishell_info *info, char **envp)
{
	info->current_dir_path = getcwd(NULL, 0);
	info->cmd_lst = NULL; // リスト初期化
	info->envp = envp;
	info->command = NULL;
	info->prev_rc = 0;
}


int		main(int argc, char *argv[], char *envp[])
{
	t_minishell_info	info;

	if (argc != 1)
	{
		red_error();
		ft_putendl_fd("Usage : ./minishell", 2);
		return (1);
	}
	// put_welcome_message();
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	set_env_info(&info, envp); //ここでinfoの中にenv情報入れる
	console_loop(&info, envp);
	(void)argc;
	(void)argv;
}
