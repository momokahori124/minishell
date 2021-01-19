/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:16:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/20 02:31:22 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void		exec_bin(t_minishell_info *info, t_cmdlst *cmd)
{
	char	**cmd_grp;
	int		return_val;
	pid_t	fork_pid;
	pid_t 	wait_pid;
	int		status;

	cmd_grp = cmd->arg;
	return_val = 0;
	if ((fork_pid = fork()) == -1)
		all_free_perror_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (fork_pid == 0)
	{
		return_val = execve(cmd_grp[0], cmd_grp, info->envp);
		if (return_val == -1)
			all_free_perror_exit(info, ERR_EXECVE, __LINE__, __FILE__);
	}
	if ((wait_pid = waitpid(fork_pid, &status, 0)) == -1)
		all_free_perror_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (WIFEXITED(status))
		return ;
	else
		all_free_perror_exit(info, ERR_FAIL_CHILD, __LINE__, __FILE__);
}

void	free_alloc_ptr_in_cmd_lst(t_cmdlst **cmd_lst)
{
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
	else
		return (s);
}

bool	execute(t_minishell_info *info, t_cmdlst *cmd)
{
	int	type;

	type = cmd->type;
	if (type == BIN)
		exec_bin(info, cmd);
	else if (type == EXIT)
		exec_exit(info);
	else if (type == PWD)
		exec_pwd(info);
	else if (type == NOT_CMD)
		info->prev_rc = put_cmd_not_found(cmd->arg[0]);
	return (true);
}

bool		execute_command(t_minishell_info *info)
{
	t_cmdlst *next;

	while (info->cmd_lst)
	{
		next = info->cmd_lst->next;
		if (next && (next->type == OUTPUT || next->type == DB_OUTPUT ||
					next->type == INPUT))
			next = redirect_sep(info, &(info->cmd_lst));
		else if (next && next->type == PIPE)
			next = pipe_sep(info, &(info->cmd_lst));
		else
		{
			execute(info, info->cmd_lst);
			// free_alloc_ptr_in_cmd_lst(&(info->cmd_lst));
		}
		info->cmd_lst = next;
	}
	info->cmd_lst = NULL;
	return (true);
}

// __attribute__((destructor))
// void end()
// {
// 	system("leaks minishell");
// }
