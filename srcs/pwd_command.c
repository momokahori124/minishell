/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:58:34 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/14 00:05:26 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

/*
** commandがpwdだった時の処理関数
*/

void		exec_pwd(t_minishell_info *info)
{
	ft_putendl_fd(info->current_dir_path, 1);
}

/*
** 各commandをリストで持つのでこれはpwdの情報をリストに繋げる関数
** この関数を出た時はパイプなどまでcommandが進むようにしていく(今はパイプしか対応していない)
*/

bool		add_pwd_to_lst(t_minishell_info *info, char **command)
{
	t_cmdlst	*pwd;

	if (!(pwd = malloc(sizeof(t_cmdlst))))
	{
		free(info->cmd_lst); // 本当はリスト全部
		free_perror_exit(*command, ERR_MALLOC, EXIT_FAILURE);
	}
	pwd->command = NULL;
	pwd->type = PWD;
	pwd->pipe[0] = 0; // わかりやすく書いてるだけであとで消す
	pwd->pipe[1] = 0;
	pwd->arg = NULL;
	pwd->next = NULL;
	cmd_lstadd_back(&(info->cmd_lst), pwd);
	*command = next_command((*command) + 3);
	return (true);
}
