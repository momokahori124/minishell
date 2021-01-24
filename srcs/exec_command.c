/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:16:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/25 00:12:15 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	free_alloc_ptr_in_cmd_lst(t_cmdlst **cmd_lst)
{
	if ((*cmd_lst)->arg != NULL)
		ptr_2d_free((void ***)&((*cmd_lst)->arg), ARG_MAX);
	ptr_free((void **)cmd_lst);
}

/*
** 構造体に持ったコマンドのタイプを元にそれに応じた処理を振り分ける関数
*/

char *typecheck(int type, char *s)
{
	if (type == PWD)
		return ("pwd");
	else if (type == OUTPUT)
		return (">");
	else if (type == DB_OUTPUT)
		return (">>");
	else if (type == INPUT)
		return ("<");
	else if (type == SEMICOLON)
		return (";");
	else
		return (s);
}

bool	execute(t_minishell_info *info, t_cmdlst *cmd)
{
	int	type;

	type = cmd->type;
	if (type == BIN)
		exec_bin(info, cmd->arg);
	else if (type == EXIT)
		exec_exit(info);
	else if (type == PWD)
		exec_pwd(info);
	else if (type == ECHO)
		exec_echo(info, cmd->arg);
	else if (type == CD)
		exec_cd(info, cmd);
	else if (type == ENV)
		exec_env(info, cmd->arg[1]);
	else if (type == EXPORT)
		exec_export(info, cmd->arg);
	else if (type == UNSET)
		exec_unset(info, cmd->arg);
	printf("exit status : %d\n", g_signal.exit_status);
	return (true);
}

bool		execute_command(t_minishell_info *info)
{
	t_cmdlst *next;

	while (info->cmd_lst)
	{
		if (info->cmd_lst->next && (info->cmd_lst->next->type == OUTPUT ||
				info->cmd_lst->next->type == DB_OUTPUT ||
				info->cmd_lst->next->type == INPUT ||
				info->cmd_lst->next->type == STDERR_OUTPUT ||
				info->cmd_lst->next->type == STDERR_DB_OUTPUT))
			info->cmd_lst = redirect_sep(info, &(info->cmd_lst));
		else if (info->cmd_lst->next && info->cmd_lst->next->type == PIPE)
			info->cmd_lst = pipe_sep(info, &(info->cmd_lst));
		else
			execute(info, info->cmd_lst);
		if (info->cmd_lst == NULL)
			break ;
		next = info->cmd_lst->next;
		free_alloc_ptr_in_cmd_lst(&(info->cmd_lst));
		info->cmd_lst = next;
	}
	info->cmd_lst = NULL;
	return (true);
}
