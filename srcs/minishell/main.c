/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 04:07:48 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/*
** info.current_dir_path = getcwd(NULL, 0); は
** pwdのためにカレントディレクトリを取得して構造体に入れている
** pwd ; pwdみたいな時に二回getcwd呼ぶの嫌だったのでそうした
*/

void		console_loop(t_minishell_info *info)
{
	char	*command;

	put_prompt(info);
	while (1)
	{
		if ((command = waiting_for_input(info)) == NULL)
			write(1, "\033[0K", 4); //これいらないかも、なんで書いたのか忘れた
		else
			if (parse_command(info, command) != false)
				execute_loop(info);
		put_prompt(info);
	}
}

int	main()
{
	t_minishell_info	info;
	extern char			**environ;

	// display_welcome_message();
	set_shell_level();
	set_minishell_info(&info); //ここでinfoの中にenv情報入れる
	set_env(&info); //ここでinfoの中にenv情報入れる
	set_prompt_message(environ, info.env);
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	console_loop(&info);
}
