/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/25 00:39:30 by tjinichi         ###   ########.fr       */
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

/*
** 各commandをリストで持つので情報をリストに繋げる関数
*/

bool		add_cmd_to_lst(t_minishell_info *info, char **command, int type)
{
	t_cmdlst	*cmd;

	if (!(cmd = malloc(sizeof(t_cmdlst))))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (type == CMD_NUM)
		cmd->type = NOT_CMD;
	else if (type == OUTPUT_PIPE)
		cmd->type = OUTPUT;
	else
		cmd->type = type;
	cmd->arg = command;
	cmd->next = NULL;
	cmd_lstadd_back(&(info->cmd_lst), cmd);
	return (true);
}

bool	cmd_exit_check(char *cmd)
{
	if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't'
		&& cmd[4] == '\0')
		return (true);
	return (false);
}

bool	check_executable_file_in_bin_dir(char *path, char ***command,
				t_minishell_info *info)
{
	t_stat	stat_buf;
	char	*bin_path;

	if (!(bin_path = ft_str3join(path, "/", (*command)[0])))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
	{
		ptr_free((void **)&((*command)[0]));
		(*command)[0] = bin_path;
		return (true);
	}
	ptr_free((void **)&bin_path);
	return (false);
}

bool	check_bash_standard_commands(t_minishell_info *info, char ***command)
{
	char		*env_path;
	char		**bin_paths;
	int			i;

	env_path = search_env("PATH", 4, info->env);
	if (!(bin_paths = ft_split(env_path, ':')))
	{
		ptr_2d_free((void ***)command, ARG_MAX);
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	i = 0;
	while (bin_paths[i])
	{
		if (check_executable_file_in_bin_dir(bin_paths[i], command, info) == true)
			break ;
		i++;
	}
	ptr_2d_free((void ***)&bin_paths, ARG_MAX);
	return (true);
}

bool	devide_semicolon_and_redirect(int type, char ***split,
						t_minishell_info *info)
{
	ptr_2d_free((void ***)split, 1);
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
	const char	*base[CMD_NUM] = {"\0", "2>", "2>>", ";", ";<", ";>", ";>>",
	"<", ">", ">>", ">|", "cd", "echo", "env", "export", "pwd", "unset", "|"};
	// 	const char	*base[CMD_NUM - 1] = {"\0", "2>", "2>>", ";", ";<", ";>", ";>>",
	// "<", ">", ">>", ">|", "cd", "echo", "export", "pwd", "unset", "|"};

	if (!(split = split_switch_env_value(command, ' ', info->env)))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (split[0] == NULL)
		return (1);
	// 先にseparatorだけでバイナリーサーチしても良い
	if (cmd_exit_check(split[0]) == true)
		return (add_cmd_to_lst(info, split, EXIT));
	type = str_bsearch(split[0], base, CMD_NUM, strcmp_regardless_of_case);
	if (type == SEMI_OUTPUT || type == SEMI_DB_OUTPUT ||
				type == SEMI_INPUT)
		return (devide_semicolon_and_redirect(type, &split, info));
	else if (type == NOT_CMD)
	{
		if (check_bash_standard_commands(info, &split) == true)
			return (add_cmd_to_lst(info, split, BIN));
	}
	add_cmd_to_lst(info, split, type);
	return (1);
}

/*
** parsing関数でparseするためにwhileを回す関数(envpは構造体に入れると思う)
** commandもinfo->commandもmalloc済
*/

bool		parse_command_line(t_minishell_info *info, char *command)
{
	char	**cmd_grp;
	int		i;

	// printf("%s\n", info->command);
	if (!(cmd_grp = split_by_separator_contain_delimiters(command)))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	cmd_grp = rm_space_in_array(cmd_grp, info);
	ptr_free((void **)&(command));
	if (check_format_of_command(&cmd_grp, info) == false)
		return (false);
	i = -1;
	while (cmd_grp[++i])
	{
		printf("[%d] : [%s]\n", i, cmd_grp[i]);
		parsing(info, cmd_grp[i]);
	}
	ptr_2d_free((void ***)&cmd_grp, i);
	return (true);
}
