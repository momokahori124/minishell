/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/20 04:37:43 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// int		is_command(char *cmd, t_minishell_info *info)
// {
// 	char		**split;
// 	const char	*base[CMD_NUM] = {"cd", "echo", "env", "exit",
// 									"export", "pwd", "unset"};

// 	(void)info;
// 	split = ft_split(cmd, ' ');
// 	if (split == NULL)
// 		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	char *tmp = split[0];
// 	while (*tmp)
// 	{
// 		*tmp = ft_tolower(*tmp);
// 		tmp++;
// 	}
// 	int	type = str_bsearch(split[0], base, CMD_NUM);
// 	info->cmd_split = split;
// 	split++;
// 	add_cmd_to_lst(info, split, type);
// 	return (type);
// }

bool	cmd_exit_check(char *cmd)
{
	if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't')
		return (true);
	return (false);
}

bool	check_bash_standard_commands(t_minishell_info *info, char **command)
{
	t_stat	stat_buf;
	char	*bin_path;

	bin_path = ft_strjoin("/bin/", command[0]);
	if (bin_path == NULL)
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
	{
		ptr_free((void **)&(command[0]));
		command[0] = bin_path;
		return (true);
	}
	ptr_free((void **)&bin_path);

	bin_path = ft_strjoin("/usr/bin/", command[0]); // makeとかのため
	if (bin_path == NULL)
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
	{
		ptr_free((void **)&(command[0]));
		command[0] = bin_path;
		return (true);
	}
	ptr_free((void **)&bin_path);
	return (false);
}

int	ft_lowerstr_cmp(char *p1, char *p2)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (!p1 || !p2)
		return (INT_MIN);
	s1 = (unsigned char *)p1;
	s2 = (unsigned char *)p2;
	while (*s1 && ft_tolower(*s1) == ft_tolower(*s2))
	{
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

bool	devide_semicolon_and_redirect(int type, t_minishell_info *info)
{
	add_cmd_to_lst(info, NULL, SEMICOLON);
	if (type == SEMI_OUTPUT)
		add_cmd_to_lst(info, NULL, OUTPUT);
	else if (type == SEMI_DB_OUTPUT)
		add_cmd_to_lst(info, NULL, DB_OUTPUT);
	else if (type == SEMI_INPUT)
		add_cmd_to_lst(info, NULL, DB_INPUT);
	return (1);
}


/*
** 入力された文字列から各コマンドをparseする関数
*/

bool	parsing(t_minishell_info *info, char *command)
{
	int			type;
	char		**split;
	// ;> ;< ;>>とかの処理もする
	const char	*base[CMD_NUM] = {"\0", ";", ";<", ";>", ";>>", "<", ">", ">>",
								">|", "cd", "echo", "env", "exit",
								"export", "pwd", "unset", "|"};

	if (!(split = ft_split(command, ' ')))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (split[0] == NULL)
		return (1);
	if (cmd_exit_check(split[0]) == true)
		return (add_cmd_to_lst(info, split, EXIT));
	type = str_bsearch(split[0], base, CMD_NUM, ft_lowerstr_cmp);
	if (type == SEMI_OUTPUT || type == SEMI_DB_OUTPUT ||
				type == SEMI_INPUT)
		return (devide_semicolon_and_redirect(type, info));
	else if (type == NOT_CMD)
		if (check_bash_standard_commands(info, split) == true)
			return (add_cmd_to_lst(info, split, BIN));
	add_cmd_to_lst(info, split, type);
	return (1);
}

/*
** parsing関数でparseするためにwhileを回す関数(envpは構造体に入れると思う)
** commandもinfo->commandもmalloc済
*/

bool		parse_command_line(t_minishell_info *info)
{
	char	**cmd_grp;
	int		i;

	// printf("%s\n", info->command);
	if (!(cmd_grp = split_by_chrs_contain_delimiters(info->command, "><;|")))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	cmd_grp = rm_space_in_array(cmd_grp, info);
	ptr_free((void **)&(info->command));
	if (check_format_of_command(&cmd_grp, info) == false)
		return (false);
	i = -1;
	while (cmd_grp[++i])
	{
		// printf("[%d] : [%s]\n", i, cmd_grp[i]);
		parsing(info, cmd_grp[i]);
	}
	ptr_2d_free((void ***)&cmd_grp, i);
	return (true);
}
