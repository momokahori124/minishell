/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:27 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/14 03:21:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

/*
** 入力された文字列から各コマンドをparseする関数
*/

static bool	parsing(t_minishell_info *info, char **command)
{
	if (ft_strncmp((*command), "pwd", 3) == 0 && \
			((*command)[3] == ' ' || (*command)[3] == '\0' || \
			(*command)[3] == ';'))
		return (add_pwd_to_lst(info, command));
	else
		put_cmd_not_found((*command));
	exit(0);
	return (1);
}

/*
** parsing関数でparseするためにwhileを回す関数(envpは構造体に入れると思う)
*/

bool		parse_command_line(t_minishell_info *info, char *envp[])
{
	char	*command;

	command = info->command;
	info->cmd_lst = NULL;
	while (*command)
	{
		parsing(info, &command);
	}
	(void)envp;
	return (1);
}

/*
** 入力待ちをする関数
** (write(0, "\033[0K", 4);はCtrl + Dを押した時に^Dみたいなのが出るのを防いでいる)
*/

char		*read_command_line(void)
{
	char	*command;
	char	*return_command;
	char	buf;
	ssize_t	rc;

	command = ft_strdup("");
	while ((rc = read(0, &buf, 1)) >= 0 && buf != '\n')
	{
		if (rc != 0)
			command = re_strjoinch(&command, ft_tolower(buf));
		else
		{
			if (command[0] == '\0' && buf != '\n')
				ctrl_d_exit(command);
			write(0, "\033[0K", 4);
		}
	}
	if (rc == -1)
		free_perror_exit(command, ERR_READ, EXIT_FAILURE);
	return_command = ft_strdup(skip_space(command));
	ptr_free((void **)&command);
	return (return_command);
}
