/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:16:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/16 21:28:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void		exec_bin(t_minishell_info *info)
{
	char	**cmd_grp;
	int		return_val;
	pid_t	fork_pid;
	int		status;
	pid_t 	wait_pid;

	cmd_grp = info->cmd_lst->arg;
	return_val = 0;
	if ((fork_pid = fork()) < 0)
		all_free_perror_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (fork_pid == 0)
	{
		errno = 0;
		return_val = execve(cmd_grp[0], cmd_grp, info->envp);
		if (return_val == -1)
			all_free_perror_exit(info, ERR_EXECVE, __LINE__, __FILE__);
	}
	if ((wait_pid = waitpid(fork_pid, &status, 0)) < 0)
		all_free_perror_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (WIFEXITED(status))
		return ;
	else
		all_free_perror_exit(info, ERR_FAIL_CHILD, __LINE__, __FILE__);
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
	else
		return (s);
}

static bool	execute(t_minishell_info *info, t_cmdlst *cmd_lst)
{
	// fprintf(stderr, "type : %s\n", typecheck(cmd_lst->type));
	if (cmd_lst->type == BIN)
		exec_bin(info);
	else if (cmd_lst->type == EXIT)
		exec_exit(info);
	else if (cmd_lst->type == PWD)
		exec_pwd(info);
	else if (cmd_lst->type == NOT_CMD)
		info->prev_rc = put_cmd_not_found(cmd_lst->arg[0]);
	return (true);
}

typedef struct	s_fd
{
	int			fd;
	int			backup_stdout;
}				t_fd;


bool	write_to_file(char *filename, int mode, t_fd *mini_fd)
{
	mini_fd->backup_stdout = dup(STDOUT_FILENO);
	mini_fd->fd = open(filename, O_CREAT | O_WRONLY | mode, 0666);
	dup2(mini_fd->fd, STDOUT_FILENO);
	close(mini_fd->fd);
	return (true);
}

void		free_alloc_ptr_in_cmd_lst(t_cmdlst **cmd_lst)
{
	ptr_2d_free((void ***)&((*cmd_lst)->arg), ARG_MAX);
	ptr_free((void **)cmd_lst);
}

t_cmdlst	*save_cmdlst_and_create_file(t_cmdlst **cmd_lst, t_cmdlst *next,
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

t_cmdlst	*return_file_for_writing(t_cmdlst **cmd_lst, int *output_type,
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
			if ((*cmd_lst)->type != OUTPUT)
				return (res);
			*output_type = (*cmd_lst)->type;
			free_alloc_ptr_in_cmd_lst(cmd_lst);
		}
		else if ((cnt & 1) == 0)
			res = save_cmdlst_and_create_file(cmd_lst, next, *output_type, info);
		*cmd_lst = next;
	}
	return (res);
}

bool	redirect_output(t_minishell_info *info, t_cmdlst **cmd_lst)
{
	// t_cmdlst	*output;
	// t_cmdlst	*next;
	t_cmdlst	*save;
	t_fd		mini_fd;
	int			output_type;
	char		*filename;
	int			cmd_type;


	cmd_type = (*cmd_lst)->type;
	save = return_file_for_writing(cmd_lst, &output_type, info);
	printf("%s\n", typecheck(output_type, save->arg[0]));
	printf("%s\n", save->arg[0]);
	// exit(0);
	filename = save->arg[0];
	if (output_type == OUTPUT)
	{
		write_to_file(filename, O_TRUNC, &mini_fd);
	}
	save->type = cmd_type;
	execute(info, save);
	*cmd_lst = save->next;
	// int i = 0;
	// while ((*cmd_lst)->arg[i])
	// 	i++;
	// ptr_2d_free((void ***)&((*cmd_lst)->arg), i);
	// i = 0;
	// while (output->arg[i])
	// 	i++;
	// ptr_2d_free((void ***)&(output->arg), i);
	// i = 0;
	// while (next->arg[i])
	// 	i++;
	// ptr_2d_free((void ***)&(next->arg), i);
	// *cmd_lst = next;
	dup2(mini_fd.backup_stdout, STDOUT_FILENO);
	return (true);
}

bool		execute_command(t_minishell_info *info)
{
	t_cmdlst *begin;
	t_cmdlst *next;

	begin = info->cmd_lst;
	while (info->cmd_lst)
	{
		// fprintf(stderr, "type : %s\n", typecheck(info->cmd_lst->type, info->cmd_lst->arg[0]));
		next = info->cmd_lst->next;
		// printf("%p\n", next);
		// if (next && next->type == OUTPUT)
		// 	if (pipe(next->pipe) < 0)
		// 		all_free_perror_exit(info, ERR_PIPE, __LINE__, __FILE__);
		if (next && next->type == OUTPUT)
		{
			redirect_output(info, &(info->cmd_lst));
			printf("%p\n", info->cmd_lst);
			continue ;
		}
		execute(info, info->cmd_lst);
		int i = 0;
		while (info->cmd_lst->arg[i])
			i++;
		ptr_2d_free((void ***)&(info->cmd_lst->arg), i);
		info->cmd_lst = info->cmd_lst->next;
	}
	info->cmd_lst = begin;
	return (true);
}

// __attribute__((destructor))
// void end()
// {
// 	system("leaks minishell");
// }
