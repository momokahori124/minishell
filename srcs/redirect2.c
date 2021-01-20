/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 02:20:13 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/21 03:00:39 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe_redirect.h"

void		read_from_file(int fd, t_cmdlst *begin, t_minishell_info *info)
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

void		write_to_file(int fd, int std, t_cmdlst *begin,
	t_minishell_info *info)
{
	int	backup;

	if ((backup = dup(std)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd, std) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	execute(info, begin);
	if (dup2(backup, std) == -1)
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

void		mix_input_and_output(int fd[3], t_cmdlst *begin,
				t_minishell_info *info)
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
}

void		mix_input_and_stderr_output(int fd[3], t_cmdlst *begin,
				t_minishell_info *info)
{
	int	backup_stdin;
	int	backup_stderr;

	if ((backup_stdin = dup(STDIN_FILENO)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd[1], STDIN_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if ((backup_stderr = dup(STDERR_FILENO)) == -1)
		all_free_perror_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd[0], STDERR_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	execute(info, begin);
	if (dup2(backup_stderr, STDERR_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd[0]) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup_stderr) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (dup2(backup_stdin, STDIN_FILENO) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd[1]) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup_stdin) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}
