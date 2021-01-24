/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:06:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/25 00:37:13 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

void		exec_bin(t_minishell_info *info, char **args)
{
	int			return_val;
	pid_t		wait_pid;
	int			status;
	extern char	**environ;

	return_val = 0;
	if ((g_signal.fork_pid = fork()) == -1)
		all_free_perror_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (g_signal.fork_pid == 0)
	{
		return_val = execve(args[0], args, environ);
		if (errno == ENOENT || errno == EACCES)
			put_cmd_not_found(args[0]);
		else if (return_val == -1)
			all_free_perror_exit(info, ERR_EXECVE, __LINE__, __FILE__);
		exit(CMD_NOT_FOUND);
	}
	errno = 0;
	if ((wait_pid = waitpid(g_signal.fork_pid, &status, 0)) == -1)
		all_free_perror_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (g_signal.exit_status != 130)
		g_signal.exit_status = WEXITSTATUS(status);
	if (WIFEXITED(status) || WEXITSTATUS(status) == 0)
		return ;
	all_free_perror_exit(info, ERR_FAIL_CHILD, __LINE__, __FILE__);
}
