/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:16:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/22 02:39:28 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int		exec_bin(t_minishell_info *info, t_cmdlst *cmd)
{
	int		return_val;
	pid_t 	wait_pid;
	int		status;

	return_val = 0;
	if ((g_bin_fork_pid = fork()) == -1)
		all_free_perror_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (g_bin_fork_pid == 0)
	{
		return_val = execve(cmd->arg[0], cmd->arg, info->envp);
		if (errno == ENOENT)
			info->prev_rc = put_cmd_not_found(cmd->arg[0]);
		else if (return_val == -1)
			all_free_perror_exit(info, ERR_EXECVE, __LINE__, __FILE__);
		exit(CMD_NOT_FOUND);
	}
	if ((wait_pid = waitpid(g_bin_fork_pid, &status, 0)) == -1)
		all_free_perror_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (WIFEXITED(status) || WEXITSTATUS(status) == 0)
		return (info->prev_rc = WEXITSTATUS(status));
	all_free_perror_exit(info, ERR_FAIL_CHILD, __LINE__, __FILE__);
	return (-1);
}

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

void		exec_echo(t_minishell_info *info, t_cmdlst *cmd)
{
	int		i;
	int		n_flag;
	char	**args;

	args = cmd->arg;
	n_flag = 0;
	if (ft_strcmp(args[1], "-n") == 0)
		n_flag = 1;
	i = 1 + n_flag;
	while (args[i])
	{
		if (ft_putstr_fd(args[i], 1) == false)
			all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (args[i + 1] == NULL && n_flag == 0)
		{
			if (write(1, " \n", 2) == -1)
				all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		else
			if (write(1, " ", 1) == -1)
				all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
		i++;
	}
}

bool	execute(t_minishell_info *info, t_cmdlst *cmd)
{
	int	type;

	type = cmd->type;
	info->prev_rc = 0;
	if (type == BIN)
		exec_bin(info, cmd);
	else if (type == EXIT)
		exec_exit(info);
	else if (type == PWD)
		exec_pwd(info);
	else if (type == ECHO)
		exec_echo(info, cmd);
	printf("prev_rc : %d\n", g_sig.exit_status);
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
