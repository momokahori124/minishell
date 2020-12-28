/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:16:47 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/29 03:43:49 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

/*
** 構造体に持ったコマンドのタイプを元にそれに応じた処理を振り分ける関数
*/

static bool	execute(t_minishell_info *info)
{
	if (info->cmd_lst->type == PWD)
		exec_pwd(info);
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
