/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:04:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 02:53:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

static void	put_newline(t_minishell_info *info)
{
	if (write(1, "\n", 1) == -1)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return ;
}

static void	put_all_first_arg(int i, t_cmdlst *cmd, t_minishell_info *info)
{
	t_cmdlst	*begin;

	begin = cmd;
	if (ft_putstr_fd(cmd->arg[i], 1) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	cmd = cmd->next;
	while (cmd)
	{
		if (cmd->type == OUTPUT || cmd->type == DB_OUTPUT)
			;
		else if (cmd->type == PIPE || cmd->type == SEMICOLON)
			break ;
		else
		{
			if (cmd->arg[1] == NULL)
				;
			else if (cmd->arg[1] != NULL)
				if (ft_putstr_fd(cmd->arg[1], STDOUT_FILENO) == false)
					all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
			if (write(1, " ", STDOUT_FILENO) == -1)
					all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
			if (cmd->next == NULL)
				if (write(STDOUT_FILENO, "\n", 1) == -1)
					all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);

		}
		cmd = cmd->next;
	}
	cmd = begin;
}

void		exec_echo(t_minishell_info *info, t_cmdlst *cmd)
{
	int			i;
	char		**args;
	int			n_flag;

	args = cmd->arg;
	if (args[1] == NULL)
		return (put_newline(info));
	n_flag = 0;
	if (args[1][0] == '-')
		if ((n_flag = 1) && ft_strcmp(args[1], "-n") != 0)
			return (error_mandatory(ERR_ECHO, 21, info));
	i = 1 + n_flag;
	if (cmd->next && (cmd->next->type == OUTPUT ||
				cmd->next->type == DB_OUTPUT))
		return (put_all_first_arg(i, cmd, info));
	while (args[i])
	{
		if (ft_putstr_fd(args[i], 1) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (args[i + 1] == NULL && n_flag == 0)
		{
			if (write(1, " \n", 2) == -1)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		else
			if (write(1, " ", 1) == -1)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		i++;
	}

}
