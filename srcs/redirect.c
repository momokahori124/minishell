/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:45:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/21 01:19:07 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe_redirect.h"

static int		read_from_file(int fd, t_cmdlst *begin, t_minishell_info *info)
{
	int	backup;

	if ((backup = dup(STDIN_FILENO)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd, STDIN_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	execute(info, begin);
	if (dup2(backup, STDIN_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
/*
** もう一つのやり方
*/
	// if ((backup_stdin = dup(STDIN_FILENO)) == -1)
	// 	all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	// if (close(STDIN_FILENO) == -1)
	// 	all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if ((fd = open(filename, O_RDONLY)) == -1)
	// {
	// 	if (dup(backup_stdin) == -1)
	// 		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	// 	if (errno == ENOENT)
	// 		return (err_no_such_file_or_directory(filename, info));
	// 	all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
	// }
	// execute(info, begin);
	// if (close(fd) == -1)
	// 	all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if (dup(backup_stdin) == -1)
	// 	all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
}

static void		write_to_file(int fd, t_cmdlst *begin, t_minishell_info *info)
{
	int	backup;

	if ((backup = dup(STDOUT_FILENO)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd, STDOUT_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	execute(info, begin);
	if (dup2(backup, STDOUT_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);

/*
** もう一つのやり方
*/
	// if ((backup_stdout = dup(STDOUT_FILENO)) == -1)
	// 	all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	// if (close(STDOUT_FILENO) == -1)
	// 	all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if ((fd = open(filename, O_CREAT | O_WRONLY | mode, 0666)) == -1)
	// 	all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
	// execute(info, begin);
	// if (close(fd) == -1)
	// 	all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if (dup(backup_stdout) == -1)
	// 	all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
}

static t_cmdlst	*save_cmdlst_and_create_file(t_cmdlst **cmd_lst, t_cmdlst *next,
					int prev_output, t_minishell_info *info)
{
	if (next && (next->type == OUTPUT || next->type == DB_OUTPUT ||
						next->type == INPUT))
	{
		if (prev_output == OUTPUT || prev_output == DB_OUTPUT)
		{
			if (open((*cmd_lst)->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0666)
						< 0)
				all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
		}
		free_alloc_ptr_in_cmd_lst(cmd_lst);
		// free(*cmd_lst);
		// *cmd_lst = NULL;
	}
	printf("%p\n", *cmd_lst);
	printf("%p\n", cmd_lst);
	return (*cmd_lst);
}

static t_cmdlst	*return_file_for_writing(t_cmdlst **cmd_lst, int *redirect_type,
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
				{
					exit(0);
				return (res);
				}
			*redirect_type = (*cmd_lst)->type;
			free_alloc_ptr_in_cmd_lst(cmd_lst);
		}
		else if ((cnt & 1) == 1)
			res = save_cmdlst_and_create_file(cmd_lst, next, \
						*redirect_type, info);
		*cmd_lst = next;
		cnt++;
	}
	return (res);
}

int		set_mode(int type)
{
	if (type == OUTPUT)
		return (O_TRUNC);
	else if (type == DB_OUTPUT)
		return (O_APPEND);
	return (0);
}

bool		open_files(int fd[2], int type, char *filename, t_minishell_info *info)
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
	return (true);
}

void	ft_close(int *fd)
{
	close(*fd);
	*fd = -1;
}

int		open_files_and_stock_fd(int fd[3], t_cmdlst **cmd_lst,
						t_minishell_info *info)
{
	t_cmdlst	*nextsep;

	while ((*cmd_lst)->next)
	{
		nextsep = (*cmd_lst)->next->next;
		if (open_files(fd, (*cmd_lst)->type, (*cmd_lst)->next->arg[0], info)
			== false)
			return (false);

		if (nextsep && (nextsep->type == OUTPUT || nextsep->type == DB_OUTPUT))
			if (fd[0] != -1)
				ft_close(&(fd[0]));
		if (nextsep && nextsep->type == INPUT)
			if (fd[1] != -1)
				ft_close(&(fd[1]));
		*cmd_lst = skip_lst_and_free(cmd_lst, 1);
		if (nextsep && (nextsep->type == PIPE || nextsep->type == SEMICOLON))
			return (true);
	}
	free_alloc_ptr_in_cmd_lst(cmd_lst);
	return (true);
}

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

int		mix_input_and_output(int fd[2], t_cmdlst *begin, t_minishell_info *info)
{
	int	backup_stdin;
	int	backup_stdout;

	if ((backup_stdin = dup(STDIN_FILENO)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd[1], STDIN_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if ((backup_stdout = dup(STDOUT_FILENO)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd[0], STDOUT_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	execute(info, begin);
	if (dup2(backup_stdout, STDOUT_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd[0]) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup_stdout) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (dup2(backup_stdin, STDIN_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd[1]) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup_stdin) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);







	// if (close(STDIN_FILENO) == -1)
	// 	all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if ((fd[0] = open(input_file, O_RDONLY)) == -1)
	// {
	// 	if (dup(backup_stdin) == -1)
	// 		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	// 	if (errno == ENOENT)
	// 		return (err_no_such_file_or_directory(input_file, info));
	// 	all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
	// }
	// fprintf(stderr, "%d\n", fd[0]);
	// if ((backup_fd[1] = dup(STDOUT_FILENO)) == -1)
	// 	all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	// if (close(STDOUT_FILENO) == -1)
	// 	all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if ((fd[1] = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
	// 	all_free_perror_exit(info, ERR_OPEN, __LINE__, __FILE__);
	// fprintf(stderr, "%d\n", fd[1]);
	// execute(info, begin);
	// if (close(fd[0]) == -1)
	// 	all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if (dup(backup_fd[0]) == -1)
	// 	all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	// if (close(fd[1]) == -1)
	// 	all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if (dup(backup_fd[1]) == -1)
	// 	all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
}

t_cmdlst		*redirect_sep(t_minishell_info *info, t_cmdlst **cmd_lst)
{
	t_cmdlst	*save;
	t_cmdlst	*begin;
	int			mode;
	char		*filename;
	char		*input_file;
	char		*output_file;
	int			fd[2];

	begin = *cmd_lst;
	*cmd_lst = (*cmd_lst)->next;
	input_file = NULL;
	output_file = NULL;
	fd[0] = -1;
	fd[1] = -1;
	if (open_files_and_stock_fd(fd, cmd_lst, info) == false)
	{
		free_alloc_ptr_in_cmd_lst(&begin);
		return (skip_lst_and_free(cmd_lst, ARG_MAX));
	}
	if (fd[0] != -1 && fd[1] != -1)
		mix_input_and_output(fd, begin, info);
	else if (fd[1] != -1)
		read_from_file(fd[1], begin, info);
	else if (fd[0] != -1)
		write_to_file(fd[0], begin, info);
	// exit(0);




	// printf("====== %s\n", typecheck(mode, NULL));
	// printf("output : %s\n", output_file);
	// printf("input  : %s\n", input_file);
	// printf("====== %s\n", typecheck((*cmd_lst)->type, NULL));
	// if (mode == -1)
	// {
	// 	puts("0");
	// 	return (skip_lst_and_free(cmd_lst, ARG_MAX));
	// }
	// if (input_file && output_file)
	// {
	// 	puts("1");
	// 	if (mix_input_and_output(input_file, output_file, begin, info) == -1)
	// 		return (skip_lst_and_free(cmd_lst, ARG_MAX));
	// }
	// else if (input_file != NULL)
	// 	read_from_file(input_file, begin, info);
	// else if (output_file != NULL)
	// {
	// 	puts("3");
	// 	if (mode == DB_OUTPUT)
	// 		write_to_file(output_file, O_APPEND, begin, info);
	// 	if (mode == OUTPUT)
	// 		write_to_file(output_file, O_TRUNC, begin, info);

	// }
	// puts("4");
	free_alloc_ptr_in_cmd_lst(&begin);
	return (*cmd_lst);







	// save = return_file_for_writing(&((*cmd_lst)->next), &redirect_type, info);
	// filename = save->arg[0];
	// *cmd_lst = save;
	// printf("[%d]\n", redirect_type);
	// if (redirect_type == OUTPUT)
	// 	write_to_file(filename, O_TRUNC, begin, info);
	// else if (redirect_type == DB_OUTPUT)
	// 	write_to_file(filename, O_APPEND, begin, info);
	// else if (redirect_type == INPUT)
	// 	read_from_file(filename, begin, info);
	// free_alloc_ptr_in_cmd_lst(&begin);
	// return (save->next);
}

// __attribute__((destructor))
// void end()
// {
// 	system("leaks minishell");
// }
