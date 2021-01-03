/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:16:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/03 23:55:52 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void		exec_bin(t_minishell_info *info)
{
	char	**cmd_grp;
	int		return_val;

	cmd_grp = info->cmd_split;
	return_val = 0;
	errno = 0;
	return_val = execve(cmd_grp[0], cmd_grp, info->envp);
	return_val = -1;
	if (return_val == -1)
	{
		puts("aaaaaaaa");
		perror("==============");
		all_free_perror_exit(info, ERR_EXECVE);
	}
}

/*
** 構造体に持ったコマンドのタイプを元にそれに応じた処理を振り分ける関数
*/

static bool	execute(t_minishell_info *info)
{
	if (info->cmd_lst->type == BIN)
	{
		exec_bin(info);
		puts("11111111111111111");
	}
	if (info->cmd_lst->type == PWD)
		exec_pwd(info);
	else if (info->cmd_lst->type == NOT_CMD)
		info->prev_rc = put_cmd_not_found(info->cmd_split[0]);
	return (1);
}

/*
** リストを回してexecute_each_command関数に渡すようにする関数
*/

bool		execute_command(t_minishell_info *info)
{
	while (info->cmd_lst)
	{
		execute(info);
		info->cmd_lst = info->cmd_lst->next;
	}
	return (1);
}
