/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:16:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/14 03:53:57 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void		exec_bin(t_minishell_info *info)
{
	char	**cmd_grp;
	int		return_val;
	pid_t	fork_pid;
	int		status;
	pid_t 	wait_pid;

	cmd_grp = info->cmd_lst->arg;
	return_val = 0;
	if ((fork_pid = fork()) < 0)
		all_free_perror_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (fork_pid == 0)
	{
		errno = 0;
		return_val = execve(cmd_grp[0], cmd_grp, info->envp);
		if (return_val == -1)
			all_free_perror_exit(info, ERR_EXECVE, __LINE__, __FILE__);
	}
	if ((wait_pid = waitpid(fork_pid, &status, 0)) < 0)
		all_free_perror_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (WIFEXITED(status))
		return ;
	else
		all_free_perror_exit(info, ERR_FAIL_CHILD, __LINE__, __FILE__);
}

void		exec_exit(t_minishell_info *info)
{
	int		count;
	bool	flag;
	char	**arg;
	int		exit_code;

	arg = info->cmd_lst->arg;
	flag = false;
	exit_code = 1;
	while (arg[count])
		count++;
	write(2, "\033[0Kexit\n", 9);
	if (arg[1] != NULL && ft_isdigit(arg[1][0]))
		flag = true;
	if (count == 1)
		exit(exit_code);
	else if (count == 2 && flag == true)
		exit(ft_atoi(arg[1]));
	else
	{
		if (flag)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			info->prev_rc = 1;
			return ;
		}
		else
		{
			// aaaはarg[1]に変えないとだめ
			write(2, "minishell: exit: aaa: numeric argument required\n", 48);
			exit(255);
		}
	}
	errno = 0;
	all_free_perror_exit(info, NULL, 0, NULL);
}

/*
** 構造体に持ったコマンドのタイプを元にそれに応じた処理を振り分ける関数
*/

static bool	execute(t_minishell_info *info)
{
	if (info->cmd_lst->type == BIN)
		exec_bin(info);
	else if (info->cmd_lst->type == EXIT)
		exec_exit(info);
	else if (info->cmd_lst->type == PWD)
		exec_pwd(info);
	else if (info->cmd_lst->type == NOT_CMD)
		info->prev_rc = put_cmd_not_found(info->cmd_lst->arg[0]);
	return (1);
}

/*
** リストを回してexecute_each_command関数に渡すようにする関数
*/

bool		execute_command(t_minishell_info *info)
{
	t_cmdlst *begin;

	begin = info->cmd_lst;
	while (info->cmd_lst)
	{
		execute(info);
		int i = 0;
		while (info->cmd_lst->arg[i])
			i++;
		ptr_2d_free((void ***)&(info->cmd_lst->arg), i);
		info->cmd_lst = info->cmd_lst->next;
	}
	info->cmd_lst = begin;
	return (true);
}
