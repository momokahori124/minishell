/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/14 02:57:21 by tjinichi         ###   ########.fr       */
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

int		main(int argc, char *argv[], char *envp[])
{
	t_minishell_info	info;

	put_welcome_message();
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	// set_env_info(info); //ここでinfoの中にenv情報入れるかも
	info.current_dir_path = getcwd(NULL, 0);
	while (1)
	{
		put_prompt(envp);
		info.command = read_command_line();
		if (info.command[0] == '\0')
			continue ;
		parse_command_line(&info, envp);
		execute_command(&info);
		free(info.cmd_lst); // リスト全部
		free(info.command);
		free(info.current_dir_path);
		exit(0);
	}
	(void)argc;
	(void)argv;
}
