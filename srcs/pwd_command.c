/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:58:34 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/29 03:44:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

/*
** commandがpwdだった時の処理関数
*/

void		exec_pwd(t_minishell_info *info)
{
	ft_putendl_fd(info->current_dir_path, STDOUT);
}

/*
** 各commandをリストで持つのでこれはpwdの情報をリストに繋げる関数
** この関数を出た時はパイプなどまでcommandが進むようにしていく(今はパイプしか対応していない)
*/

bool		add_pwd_to_lst(t_minishell_info *info, char *command)
{
	t_cmdlst	*pwd;

	(void)command;
	if (!(pwd = malloc(sizeof(t_cmdlst))))
		all_free_perror_exit(info, ERR_MALLOC);
	pwd->command = NULL;
	pwd->type = PWD;
	pwd->pipe[0] = 0; // わかりやすく書いてるだけであとで消す
	pwd->pipe[1] = 0;
	pwd->arg = NULL;
	pwd->next = NULL;
	cmd_lstadd_back(&(info->cmd_lst), pwd);
	return (true);
}
