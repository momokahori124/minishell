/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:45:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/21 03:03:36 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe_redirect.h"

static int		set_mode(int type)
{
	if (type == OUTPUT)
		return (O_TRUNC);
	else if (type == DB_OUTPUT)
		return (O_APPEND);
	else if (type == STDERR_OUTPUT)
		return (O_TRUNC);
	else if (type == STDERR_DB_OUTPUT)
		return (O_APPEND);
	return (0);
}

static bool		open_files(int fd[2], int type, char *filename, t_minishell_info *info)
{
	int mode;

	mode = 0;
	if (type == OUTPUT || type == DB_OUTPUT)
	{
		mode = set_mode(type);
		if ((fd[0] = open(filename, O_CREAT | O_WRONLY | mode, 0666)) == -1)
			all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
	}
	else if (type == INPUT)
	{
		if ((fd[1] = open(filename, O_RDONLY)) == -1)
		{
			if (errno == ENOENT)
				return (err_no_such_file_or_directory(
					filename, info));
			all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
		}
	}
	else if (type == STDERR_OUTPUT || type == STDERR_OUTPUT)
	{
		mode = set_mode(type);
		if ((fd[2] = open(filename, O_CREAT | O_WRONLY | mode, 0666)) == -1)
			all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
	}
	return (true);
}

static int		check_last_redir_and_close_fd(int fd[3], t_cmdlst *next_sep)
{
	if (next_sep && (next_sep->type == OUTPUT || next_sep->type == DB_OUTPUT))
	{
		if (fd[0] != -1)
			if (ft_close(&(fd[0])) == false)
				return (-1);
		if (fd[2] != -1)
			if (ft_close(&(fd[1])) == false)
				return (-1);
	}
	if (next_sep && next_sep->type == INPUT)
		if (fd[1] != -1)
			if (ft_close(&(fd[1])) == false)
				return (-1);
	if (next_sep && (next_sep->type == STDERR_OUTPUT ||
				next_sep->type == STDERR_DB_OUTPUT))
	{
		if (fd[2] != -1)
			if (ft_close(&(fd[1])) == false)
				return (-1);
		if (fd[0] != -1)
			if (ft_close(&(fd[0])) == false)
				return (-1);
	}
	return (true);
}

static int		open_files_and_stock_fd(int fd[3], t_cmdlst **cmd_lst,
						t_minishell_info *info)
{
	t_cmdlst	*next_sep;

	while ((*cmd_lst)->next)
	{
		next_sep = (*cmd_lst)->next->next;
		if (open_files(fd, (*cmd_lst)->type, (*cmd_lst)->next->arg[0], info)
			== false)
			return (false);
		check_last_redir_and_close_fd(fd, next_sep);
		// if (next_sep && (next_sep->type == OUTPUT || next_sep->type == DB_OUTPUT))
		// 	if (fd[0] != -1)
		// 		if (ft_close(&(fd[0])) == false)
		// 			return (-1);
		// if (next_sep && next_sep->type == INPUT)
		// 	if (fd[1] != -1)
		// 		if (ft_close(&(fd[1])) == false)
		// 				return (-1);
		*cmd_lst = skip_lst_and_free(cmd_lst, 1);
		if (next_sep && (next_sep->type == PIPE || next_sep->type == SEMICOLON))
			return (true);
	}
	free_alloc_ptr_in_cmd_lst(cmd_lst);
	return (true);
}

t_cmdlst		*redirect_sep(t_minishell_info *info, t_cmdlst **cmd_lst)
{
	t_cmdlst	*begin;
	int			rc;
	int			fd[3];

	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	begin = *cmd_lst;
	*cmd_lst = (*cmd_lst)->next;
	rc = open_files_and_stock_fd(fd, cmd_lst, info);
	printf("fd[0] : %d\n", fd[0]);
	printf("fd[1] : %d\n", fd[1]);
	printf("fd[2] : %d\n", fd[2]);
	if (rc == false || rc == -1)
	{
		free_alloc_ptr_in_cmd_lst(&begin);
		if (rc == false)
			return (skip_lst_and_free(cmd_lst, ARG_MAX));
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	if (fd[0] != -1 && fd[1] != -1)
		mix_input_and_output(fd, begin, info);
	if (fd[2] != -1 && fd[1] != -1)
		mix_input_and_stderr_output(fd, begin, info);
	if (fd[1] != -1)
		read_from_file(fd[1], begin, info);
	if (fd[2] != -1)
		write_to_file(fd[2], STDERR_FILENO, begin, info);
	if (fd[0] != -1)
		write_to_file(fd[0], STDOUT_FILENO, begin, info);
	free_alloc_ptr_in_cmd_lst(&begin);
	return (*cmd_lst);
}
