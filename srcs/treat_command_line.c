/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/13 22:36:57 by tjinichi         ###   ########.fr       */
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

static bool	check_bash_standard_commands(t_minishell_info *info, char **command)
{
	t_stat	stat_buf;
	char	*bin_path;

	info->cmd_split = command;
	bin_path = ft_strjoin("/bin/", command[0]);
	if (bin_path == NULL)
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
	{
		ptr_free((void **)&(info->cmd_split[0]));
		info->cmd_split[0] = bin_path;
		return (true);
	}
	ptr_free((void **)&bin_path);

	bin_path = ft_strjoin("/usr/bin/", command[0]); // makeとかのため
	if (bin_path == NULL)
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
	{
		ptr_free((void **)&(info->cmd_split[0]));
		info->cmd_split[0] = bin_path;
		return (true);
	}
	ptr_free((void **)&bin_path);
	return (false);
}

/*
** 入力された文字列から各コマンドをparseする関数
*/

bool	parsing(t_minishell_info *info, char *command)
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
	if (type == NOT_CMD)
	{
		if (check_bash_standard_commands(info, split) == true)
			return (add_cmd_to_lst(info, split, BIN));
	}
	// split++;
	add_cmd_to_lst(info, split, type);
	return (1);
}

bool	spaces_or_not_in_array(char **arr, int *element_num, int *i)
{
	bool	flag;

	*i = -1;
	*element_num = 0;
	flag = false;
	while (arr[++(*i)])
	{
		if (arr[(*i)][0] == ' ')
		{
			if (skip_space(arr[(*i)])[0] == '\0')
				flag = true;
		}
		else
			(*element_num)++;
	}
	return (flag);
}

char	**create_no_spaces_array(char **new, char **old)
{
	int		i;
	int		new_index;

	i = -1;
	new_index = 0;
	while (old[++i])
	{
		if (old[i][0] == ' ')
		{
			if (skip_space(old[i])[0] == '\0')
				ptr_free((void **)&old[i]);
		}
		else
			new[new_index++] = old[i];
	}
	new[new_index] = NULL;
	return (new);
}


char	**rm_space_in_array(char **arr, t_minishell_info *info)
{
	int		i;
	int		element_num;
	char	**res;

	if (spaces_or_not_in_array(arr, &element_num, &i) == false)
		return (arr);
	if (!(res = malloc(sizeof(char *) * (element_num + 1))))
	{
		ptr_2d_free((void ***)&arr, i);
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	res = create_no_spaces_array(res, arr);
	ptr_2d_free((void ***)&arr, 0);
	return (res);
}


bool	check_format_of_command(char ***grp, t_minishell_info *info)
{
	int	i;

	i = 0;
	while ((*grp)[i])
	{
		puts("=======================");
		if (i != 0 && (*grp)[i][0] == '|' && (*grp)[i][1] != '|' && !(*grp)[i + 1])
			if ((*grp = wait_for_next_cmd(grp, i + 1, info)) == NULL)
				return (false);
		if ((*grp)[0][0] == '|' && !(*grp)[i + 1])
			// return (free_and_syntax_error(PIPE, NULL, grp, info));
			;
		else if ((*grp)[0][0] == '|' && (*grp)[0][1] == '|' && !(*grp)[i + 1])
			// return (free_and_syntax_error(NOT_CMD, NULL, grp, info));
			;
		else if (i == 0 && !(*grp)[i + 1] && (*grp)[i][0] == '<' && (*grp)[i][1] == '<')
			return (syntax_error(NOT_CMD, info));
		else if (i == 0 && !(*grp)[i + 1] && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<'))
		{
			// printf("i : %d\n", i);
			return (syntax_error(NEWLINE, info));
		}
		else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '>' && (*grp)[i - 1][1] == '>')
			return (syntax_error(DB_OUTPUT, info));
		else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '>' && (*grp)[i - 1][1] == '|')
			return (syntax_error(NOT_CMD, info));
		else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '>' && (*grp)[i - 1][1] != '>')
			return (syntax_error(OUTPUT, info));
		else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == ';' && (*grp)[i - 1][1] == ';')
			return (syntax_error(NOT_CMD, info));
		else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == ';' && (*grp)[i - 1][1] != ';')
			return (syntax_error(SEMICOLON, info));
		else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '|' && (*grp)[i - 1][1] == '|')
			return (syntax_error(PIPE, info));
		else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '|' && (*grp)[i - 1][1] != '|')
			return (syntax_error(NOT_CMD, info));
		else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '<' && (*grp)[i - 1][1] == '<')
			return (syntax_error(NOT_CMD, info));
		i++;
	}
	// if (i > 1 && (*grp)[i - 1][0] == '|' && (*grp)[i - 1][1] != '|')
	// {
	// 	if ((*grp = wait_for_next_cmd(grp, i, info)) == NULL)
	// 		return (false);
	// }
	// else if (i > 2 && ((*grp)[i - 2][0] == '>' || (*grp)[i - 2][0] == '<') && (*grp)[i - 1][0] == '>' && (*grp)[i - 1][1] == '>')
	// 	return (syntax_error(DB_OUTPUT, info));
	// else if (i > 2 && (ft_strncmp((*grp)[i - 2], ">>", 2) || ft_strncmp((*grp)[i - 2], "<<", 2)) && (*grp)[i - 1][0] == '>' && (*grp)[i - 1][1] == '>')
	// 	return (syntax_error(DB_OUTPUT, info));
	// else if (i > 1 && (*grp)[i - 1][0] == '>' && (*grp)[i - 1][1] == '>')
	// 	return (syntax_error(NEWLINE, info));
	return (true);
}


/*
** parsing関数でparseするためにwhileを回す関数(envpは構造体に入れると思う)
** commandもinfo->commandもmalloc済
*/

bool		parse_command_line(t_minishell_info *info)
{
	char	**cmd_grp;
	int		i;

	printf("%s\n", info->command);
	if (!(cmd_grp = split_by_chrs_contain_delimiters(info->command, "><;|")))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	cmd_grp = rm_space_in_array(cmd_grp, info);
	ptr_free((void **)&(info->command));
	if (check_format_of_command(&cmd_grp, info) == false)
		return (false);
	// i = 0;
	// while (cmd_grp[i])
	// 	i++;
	// if (i > 1 && cmd_grp[i - 1][0] == '|' && cmd_grp[i - 1][1] != '|')
	// {
	// 	if ((cmd_grp = wait_for_next_cmd(&cmd_grp, i, info)) == NULL)
	// 		return (false);
	// }
	// if (i == 1 && cmd_grp[i - 1][0] == '|' && cmd_grp[i - 1][1] != '|')
	// 	return (syntax_error(PIPE, info));
	// else if (i > 2 && (cmd_grp[i - 2][0] == '>' || cmd_grp[i - 2][0] == '<') && cmd_grp[i - 1][0] == '>' && cmd_grp[i - 1][1] == '>')
	// 	return (syntax_error(DB_OUTPUT, info));
	// else if (i > 2 && (ft_strncmp(cmd_grp[i - 2], ">>", 2) || ft_strncmp(cmd_grp[i - 2], "<<", 2)) && cmd_grp[i - 1][0] == '>' && cmd_grp[i - 1][1] == '>')
	// 	return (syntax_error(DB_OUTPUT, info));
	// else if (i > 1 && cmd_grp[i - 1][0] == '>' && cmd_grp[i - 1][1] == '>')
	// 	return (syntax_error(NEWLINE, info));
	i = -1;
	while (cmd_grp[++i])
	{
		printf("[%d] : [%s]\n", i, cmd_grp[i]);
		parsing(info, cmd_grp[i]);
	}
	ptr_2d_free((void ***)&cmd_grp, i);
	return (true);
}

// void	rm_chr_in_str(char **str, char chr)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while ((*str)[i])
// 	{
// 		if ((*str)[i] != chr)
// 		{
// 			(*str)[j] = (*str)[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	(*str)[j] = '\0';
// }

// void	remove_quotation(char quo, char **command)
// {

// }



bool wait_quo(char first_appear, char **command)
{
	int		rc;
	char	buf = '\0';
	int		quotation_num = 0;
	(void)quotation_num;

	write(1, "> ", 2);
	*command = re_strjoinch(command, '\n');
	if (*command == NULL)
		// all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		return (false);
	while (buf != first_appear && (rc = read(0, &buf, 1)) > 0)
	// while ((rc = read(0, &buf, 1)) > 0 && !(quotation_num != 0 && quotation_num % 2 == 0))
	{
		// if (rc == 1 && buf == '\n')
		// 	continue ;
		// printf("->%d\n", rc);
		// fflush(stdout);
		// puts("+");
		write(0, "\033[0K", 4);
		// if (rc != 0 && buf == '\n')
		if (buf == '\n')
			write(1, "> ", 2);
		if (buf == first_appear)
			quotation_num++;
		// if (quotation_num == 1)
		// 	exit(9);
		*command = re_strjoinch(command, buf);
		if (*command == NULL)
			// all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
			return (false);
	}
	char a = 'a';
	// // if (quotation_num % 2 == 0 && quotation_num != 0)
	// // 	if (a == '\n')
	while (a != '\n')
		read(0, &a, 1);
	printf("[%d]\n", quotation_num);
	// rc = read(0, &buf, 1);
	if (rc == 0)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 0);
		ft_putchar_fd(first_appear, 1);
		ft_putstr_fd("`", 1);
		ft_putstr_fd("\nminishell: syntax error: unexpected end of file\n", 1);
		return (false);
	}
	// *command = re_strjoinch(command, first_appear);
	printf("[%s]\n", *command);
	return (true);
}


/*
** 入力待ちをする関数
** (write(0, "\033[0K", 4);はCtrl + Dを押した時に^Dみたいなのが出るのを防いでいる)
*/

// bool		read_command_line(t_minishell_info *info)
// {
// 	char	*command;
// 	char	buf[2];
// 	ssize_t	rc;

// 	put_prompt(info->envp, info);
// 	if (!(command = ft_strdup("")))
// 		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	buf[0] = '\0';
// 	buf[1] = '\0';
// 	while ((rc = safe_read(&(buf[0]), &command, info)) >= 0 && buf[0] != '\n')
// 	{
// 		write(0, "\033[0K", 4);
// 		if (buf[1] == buf[0] && buf[0] != '\0')
// 		{
// 			rm_chr_in_str(&command, buf[1]);
// 			buf[1] = '\0';
// 			continue ;
// 		}
// 		else if (buf[0] == '\'' || buf[0] == '\"')
// 			buf[1] = buf[0];
// 		if (rc != 0)
// 			command = re_strjoinch(&command, buf[0]);
// 		else
// 			if (buf[0] == '\0')
// 				ctrl_d_exit(command, info);
// 	}
// 	if (buf[1] == '\'' || buf[1] == '\"')
// 		return (wait_quotation(buf[1], &command, info));
// 	info->command = command;
// 	printf("+%p+\n", info->command);
// 	return (true);
// }
