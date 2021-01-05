/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/06 06:51:18 by tjinichi         ###   ########.fr       */
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


int		is_command(char *cmd, t_minishell_info *info)
{
	char		**split;
	const char	*base[CMD_NUM] = {"cd", "echo", "env", "exit",
									"export", "pwd", "unset"};

	(void)info;
	split = ft_split(cmd, ' ');
	if (split == NULL)
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	char *tmp = split[0];
	while (*tmp)
	{
		*tmp = ft_tolower(*tmp);
		tmp++;
	}
	int	type = str_bsearch(split[0], base, CMD_NUM);
	info->cmd_split = split;
	split++;
	add_cmd_to_lst(info, split, type);
	return (type);
}

static bool	cmd_exit_check(char *cmd)
{
	if ((cmd[0] == 'e' || cmd[0] == 'E') && \
		(cmd[1] == 'x' || cmd[1] == 'X') && \
		(cmd[2] == 'i' || cmd[2] == 'I') && \
		(cmd[3] == 't' || cmd[3] == 'T'))
		return (true);
	return (false);
}

static bool	check_bash_standard_commands(t_minishell_info *info, char *command)
{
	t_stat	stat_buf;
	char	*bin_path;

	bin_path = ft_strjoin("/bin/", command);
	if (bin_path == NULL)
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
	{
		ptr_free((void **)&(info->cmd_split[0]));
		info->cmd_split[0] = bin_path;
		return (true);
	}
	ptr_free((void **)&bin_path);

	bin_path = ft_strjoin("/usr/bin/", command); // makeとかのため
	if (bin_path == NULL)
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
	{
		ptr_free((void **)&(info->cmd_split[0]));
		info->cmd_split[0] = bin_path;
		return (true);
	}
	return (false);
}

/*
** 入力された文字列から各コマンドをparseする関数
*/

static bool	parsing(t_minishell_info *info, char *command)
{
	int			type;
	char		**split;
	const char	*base[CMD_NUM] = {"\0", ";", "<", ">", ">>", ">|", "cd", "echo",
							"env", "exit", "export", "pwd", "unset", "|"};

	split = ft_split(command, ' ');
	if (split == NULL)
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (split[0] == NULL)
		return (1);
	if (cmd_exit_check(split[0]) == false)
		str_tolower(&(split[0]));
	type = str_bsearch(split[0], base, CMD_NUM);
	info->cmd_split = split;
	if (type == NOT_CMD)
	{
		if (check_bash_standard_commands(info, split[0]) == true)
			return (add_cmd_to_lst(info, split, BIN));
	}
	split++;
	add_cmd_to_lst(info, split, type);
	return (1);
}

// /*
// ** 入力された文字列から各コマンドをparseする関数
// */

// static bool	parsing(t_minishell_info *info, char *command)
// {
// 	int	rc;

// 	if ((rc = is_command("pwd", skip_space(command), info)) == 1 ||
// 		(rc = is_command("echo", skip_space(command), info)) == 1)
// 		return (add_pwd_to_lst(info, command));
// 	// // else if ()
// 	else
// 		info->prev_rc = put_cmd_not_found((&(info->command)));
// 	exit(1);
// 	return (1);
// }

/*
** parsing関数でparseするためにwhileを回す関数(envpは構造体に入れると思う)
** commandもinfo->commandもmalloc済
*/

bool		parse_command_line(t_minishell_info *info, char *envp[])
{
	char	**cmd_grp;
	bool	rc;
	int		i;

	rc = true;
	if (info->command[0] == '\0')
		return (false);

	// rc = rm_quotation(info);
	// if (rc == false)
	// 	return (false);
	if (rc == true)
		rc = wait_pipe_or_redirect_next_cmd(info);
	if (rc == true)
		cmd_grp = split_by_chrs_contain_delimiters(info->command, "|;><");
	if (rc == false)
		return (false);
	// if (rc == false)
	// 	all_free_perror_exit(info, ERR_EXECVE, __LINE__, __FILE__); // ERR_EXECVEかえる
	i = 0;
	while (cmd_grp[i])
	{
		printf("%d : %s\n", i, cmd_grp[i]);
		parsing(info, cmd_grp[i]);
		i++;
	}
	(void)envp;
	// exit(0);
	return (true);
}

void	rm_chr_in_str(char **str, char chr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != chr)
		{
			(*str)[j] = (*str)[i];
			j++;
		}
		i++;
	}
	(*str)[j] = '\0';
}

// void	remove_quotation(char quo, char **command)
// {

// }



static bool wait_quo(char first_appear, char **command)
{
	int		rc;
	char	buf;

	write(1, "> ", 2);
	*command = re_strjoinch(command, '\n');
	if (*command == NULL)
		// all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		return (false);
	while ((rc = read(0, &buf, 1)) > 0 && buf != first_appear)
	{
		// if (rc == 1 && buf == '\n')
		// 	continue ;
		// printf("->%d\n", rc);
		// fflush(stdout);
		write(0, "\033[0K", 4);
		if (rc != 0 && buf == '\n')
			write(1, "> ", 2);
		// if (buf == first_appear)
		// 	break ;
		else
			*command = re_strjoinch(command, buf);
		if (*command == NULL)
			// all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
			return (false);
	}
	if (rc == 0)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 0);
		ft_putchar_fd(first_appear, 1);
		ft_putstr_fd("`", 1);
		ft_putstr_fd("\nminishell: syntax error: unexpected end of file\n", 1);
		return (false);
	}
	*command = re_strjoinch(command, first_appear);
	// return (false);
	return (true);
}


/*
** 入力待ちをする関数
** (write(0, "\033[0K", 4);はCtrl + Dを押した時に^Dみたいなのが出るのを防いでいる)
*/

bool		read_command_line(t_minishell_info *info)
{
	char	*command;
	char	buf[2];
	int	flag;
	ssize_t	rc;

	if (info->prev_rc == 2000)
		return (1);
	command = ft_strdup("");
	buf[0] = '\0';
	buf[1] = '\0';
	flag = true;
	// printf("command = [%s]\n", info->command);
	// fflush(stdout);
	while ((rc = read(0, &(buf[0]), 1)) >= 0 && buf[0] != '\n')
	{
		write(0, "\033[0K", 4);
		// write(STDOUT_FILENO, "  \b\b", 4);
		if (buf[1] == buf[0] && buf[0] != '\0')
		{
			rm_chr_in_str(&command, buf[1]);
			buf[1] = '\0';
			continue ;
		}
		else if (buf[0] == '\'' || buf[0] == '\"')
			buf[1] = buf[0];
		if (rc != 0)
			command = re_strjoinch(&command, buf[0]);
		else
			// if (command[0] == '\0' && buf[0] != '\n')
			if (buf[0] == '\0')
				ctrl_d_exit(command, info);
	}
	if (buf[1] == '\'' || buf[1] == '\"')
	{
		flag = wait_quo(buf[1], &command);
		info->prev_rc = 2000;
	}
	info->command = command;
	if (rc == -1)
		all_free_perror_exit(info, ERR_READ, __LINE__, __FILE__);
	// printf("\ncommand = [%s]\n", info->command);
	// fflush(stdout);
	// printf("flag = %d\n", flag);
	// fflush(stdout);
	// printf("rc = %ld\n", rc);
	// fflush(stdout);
	// printf("buf[0] = [%c]\n", buf[0]);
	// fflush(stdout);
	// printf("command = [%s]\n", info->command);
	// fflush(stdout);
	return (flag);
}
