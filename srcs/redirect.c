/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:45:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/18 04:21:01 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe_redirect.h"

static void		read_from_file(char *filename, t_cmdlst *begin, t_minishell_info *info)
{
	int	fd;
	int	backup_stdin;

	if ((backup_stdin = dup(STDIN_FILENO)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (close(STDIN_FILENO) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		if (dup(backup_stdin) == -1)
			all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
		if (errno == ENOENT)
			return (err_no_such_file_or_directory(filename, info));
		all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
	}
	execute(info, begin);
	if (close(fd) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (dup(backup_stdin) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
}

static void		write_to_file(char *filename, int mode, t_cmdlst *begin, \
						t_minishell_info *info)
{
	int	fd;
	int	backup_stdout;

	if ((backup_stdout = dup(STDOUT_FILENO)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (close(STDOUT_FILENO) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if ((fd = open(filename, O_CREAT | O_WRONLY | mode, 0666)) == -1)
		all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
	execute(info, begin);
	if (close(fd) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (dup(backup_stdout) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
}

static t_cmdlst	*save_cmdlst_and_create_file(t_cmdlst **cmd_lst, t_cmdlst *next,
					int prev_output, t_minishell_info *info)
{
	if (next && (next->type == OUTPUT || next->type == DB_OUTPUT || next->type == INPUT))
	{
		if (prev_output == OUTPUT || prev_output == DB_OUTPUT)
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

	cnt = 0;
	while ((*cmd_lst))
	{
		next = (*cmd_lst)->next;
		if ((cnt & 1) == 0)
		{
			if ((*cmd_lst)->type != OUTPUT && (*cmd_lst)->type != DB_OUTPUT
				&& (*cmd_lst)->type != INPUT)
				return (res);
			*output_type = (*cmd_lst)->type;
			free_alloc_ptr_in_cmd_lst(cmd_lst);
		}
		else if ((cnt & 1) == 1)
			res = save_cmdlst_and_create_file(cmd_lst, next, \
						*output_type, info);
		*cmd_lst = next;
		cnt++;
	}
	return (res);
}

t_cmdlst		*redirect_sep(t_minishell_info *info, t_cmdlst **cmd_lst)
{
	t_cmdlst	*save;
	t_cmdlst	*begin;
	int			output_type;
	char		*filename;

	begin = *cmd_lst;
	save = return_file_for_writing(&((*cmd_lst)->next), &output_type, info);
	filename = save->arg[0];
	*cmd_lst = save;
	if (output_type == OUTPUT)
		write_to_file(filename, O_TRUNC, begin, info);
	else if (output_type == DB_OUTPUT)
		write_to_file(filename, O_APPEND, begin, info);
	else if (output_type == INPUT)
		read_from_file(filename, begin, info);
	free_alloc_ptr_in_cmd_lst(&begin);
	return (save->next);
}
