/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix_input_and_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:25:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 02:53:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipe_redirect.h"

void		mix_input_and_output(int fd[3], t_cmdlst *begin,
				t_minishell_info *info)
{
	int	backup_stdin;
	int	backup_stdout;

	if ((backup_stdin = dup(STDIN_FILENO)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd[1], STDIN_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if ((backup_stdout = dup(STDOUT_FILENO)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd[0], STDOUT_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	execute(info, begin);
	if (dup2(backup_stdout, STDOUT_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd[0]) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup_stdout) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (dup2(backup_stdin, STDIN_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd[1]) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup_stdin) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}