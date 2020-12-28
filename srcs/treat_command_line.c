/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:27 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/29 03:58:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// void	is_command(char *command)
// {
// }

// char	**argument(char **command)
// {
// 	char	**res;

// 	res = split_by_str(*command, "")
// }



// bool		add_echo_to_lst(t_minishell_info *info, char **command)
// {
// 	t_cmdlst	*echo;

// 	if (!(echo = malloc(sizeof(t_cmdlst))))
// 		all_free_perror_exit(info, ERR_MALLOC);
// 	echo->command = NULL;
// 	echo->type = ECHO;
// 	echo->pipe[0] = 0; // わかりやすく書いてるだけであとで消す
// 	echo->pipe[1] = 0;
// 	echo->arg = argument(command);
// 	echo->next = NULL;
// 	cmd_lstadd_back(&(info->cmd_lst), echo);
// 	*command = next_command((*command) + 4);
// 	// puts("______________");
// 	printf("[%s]\n", echo->arg);
// 	fflush(stdout);
// 	// puts("______________");
// 	return (true);
// }


int		is_command(char *cmd_check, char *cmd, t_minishell_info *info)
{
	// const char	*s = cmd_check;
	char		**split;

	(void)info;
	split = ft_split(cmd, ' ');
	// if (split == NULL)
	// 	error ;

	if (split[0] != NULL)
	{
		while (*cmd_check && *cmd_check == ft_tolower(*cmd))
		{
			cmd++;
			cmd_check++;
		}
		if (*cmd == ' ')
			*cmd = '\0';
		if (*cmd_check == *cmd)
			return (1);
		return (0);
	}
	return (2);
}


/*
** 入力された文字列から各コマンドをparseする関数
*/

static bool	parsing(t_minishell_info *info, char *command)
{
	int	rc;

	if ((rc = is_command("pwd", skip_space(command), info)) == 1)
		return (add_pwd_to_lst(info, command));
	// // else if ()
	else
		info->prev_rc = put_cmd_not_found((&(info->command)));
	exit(1);
	return (1);
}

/*
** parsing関数でparseするためにwhileを回す関数(envpは構造体に入れると思う)
** commandもinfo->commandもmalloc済
*/

bool		parse_command_line(t_minishell_info *info, char *envp[])
{
	char	**cmd_grp;
	bool	rc;

	rc = rm_quotation(info);
	// printf("[%s]\n", info->command);
	if (rc == true)
		rc = wait_pipe_or_redirect_next_cmd(info);
	if (rc == true)
		cmd_grp = split_by_str(info->command, "|;><");
	int i = 0;
	while (cmd_grp[i])
	{
		printf("%d : %s\n", i, cmd_grp[i]);
		parsing(info, cmd_grp[i]);
		i++;
	}
	// command = str_tolower(info->command);
	// info->cmd_lst = NULL;
	// while (rc == true && *command)
	// {
	// 	parsing(info, &command);
	// }
	(void)envp;
	(void)rc;
	// exit(0);
	return (1);
}

/*
** 入力待ちをする関数
** (write(0, "\033[0K", 4);はCtrl + Dを押した時に^Dみたいなのが出るのを防いでいる)
*/

char		*read_command_line(void)
{
	char	*command;
	// char	*return_command;
	char	buf;
	ssize_t	rc;

	command = ft_strdup("");
	while ((rc = read(0, &buf, 1)) >= 0 && buf != '\n')
	{
		write(0, "\033[0K", 4);
		if (rc != 0)
			command = re_strjoinch(&command, buf);
		else
		{
			if (command[0] == '\0' && buf != '\n')
				ctrl_d_exit(command);
		}
	}
	if (rc == -1)
		free_perror_exit(command, ERR_READ);
	// return_command = ft_strdup(skip_space(command));
	// ptr_free((void **)&command);
	// return (return_command);
	return (command);
}
