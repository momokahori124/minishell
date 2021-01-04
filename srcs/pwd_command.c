/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:58:34 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/04 19:10:25 by tjinichi         ###   ########.fr       */
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
*/

bool		add_cmd_to_lst(t_minishell_info *info, char **command, int type)
{
	t_cmdlst	*cmd;

	if (!(cmd = malloc(sizeof(t_cmdlst))))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (type == CMD_NUM)
		cmd->type = NOT_CMD;
	else if (type == OUTPUT_PIPE)
		cmd->type = OUTPUT;
	else
		cmd->type = type;
	cmd->pipe[0] = 0; // わかりやすく書いてるだけであとで消す
	cmd->pipe[1] = 0;
	cmd->arg = command;
	cmd->next = NULL;
	cmd_lstadd_back(&(info->cmd_lst), cmd);
	return (true);
}
