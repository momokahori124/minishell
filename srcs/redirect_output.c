/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:45:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/17 19:48:47 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

static void		write_to_file(char *name[2], int mode, int type, \
						t_minishell_info *info)
{
	int	fd;
	int	backup_stdout;

	if ((backup_stdout = dup(STDOUT_FILENO)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (close(STDOUT_FILENO) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if ((fd = open(name[1], O_CREAT | O_WRONLY | mode, 0666)) == -1)
		all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
	execute(info, type, name[0]);
	if (close(fd) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (dup(backup_stdout) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
}

static t_cmdlst	*save_cmdlst_and_create_file(t_cmdlst **cmd_lst, t_cmdlst *next,
					int prev_output, t_minishell_info *info)
{
	if (next && (next->type == OUTPUT || next->type == DB_OUTPUT))
	{
		if (prev_output == OUTPUT)
		{
			if (open((*cmd_lst)->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0666)
						< 0)
				all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
		}
		free_alloc_ptr_in_cmd_lst(cmd_lst);
	}
	return (*cmd_lst);
}

static t_cmdlst	*return_file_for_writing(t_cmdlst **cmd_lst, int *output_type,
				t_minishell_info *info)
{
	t_cmdlst	*res;
	t_cmdlst	*next;
	int			cnt;

	cnt = -1;
	while ((*cmd_lst))
	{
		next = (*cmd_lst)->next;
		if ((++cnt & 1) == 1)
		{
			if ((*cmd_lst)->type != OUTPUT && (*cmd_lst)->type != DB_OUTPUT)
				return (res);
			*output_type = (*cmd_lst)->type;
			free_alloc_ptr_in_cmd_lst(cmd_lst);
		}
		else if ((cnt & 1) == 0)
			res = save_cmdlst_and_create_file(cmd_lst, next, \
						*output_type, info);
		*cmd_lst = next;
	}
	return (res);
}

t_cmdlst		*redirect_output(t_minishell_info *info, t_cmdlst **cmd_lst)
{
	t_cmdlst	*save;
	int			output_type;
	int			cmd_type;
	char		*name[2];

	name[0] = (*cmd_lst)->arg[0];
	cmd_type = (*cmd_lst)->type;
	save = return_file_for_writing(cmd_lst, &output_type, info);
	name[1] = save->arg[0];
	*cmd_lst = save;
	if (output_type == OUTPUT)
		write_to_file(name, O_TRUNC, cmd_type, info);
	else if (output_type == DB_OUTPUT)
		write_to_file(name, O_APPEND, cmd_type, info);
	return (save->next);
}
