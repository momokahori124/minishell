/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/25 16:15:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe_redirect.h"


void	close_pipe_fd(int pipefd[2], t_minishell_info *info)
{
	if (close(pipefd[STDIN_FILENO]) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(pipefd[STDOUT_FILENO]) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}

void	connect_std_in_out_and_pipe(int pipefd[2], int i_o,
				t_minishell_info *info)
{
	if (dup2(pipefd[i_o], i_o) == -1)
		all_free_perror_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(pipefd[STDIN_FILENO]) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(pipefd[STDOUT_FILENO]) == -1)
		all_free_perror_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}
