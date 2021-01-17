/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:50:48 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/17 23:38:14 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"

/*
** エラーメッセージとエラーが起きた場所をを出力してexitする関数。
*/

void		perror_exit(char *error_message, int line_num, char *file_name)
{
	char	*location_message;
	char	*tmp;

	red_error();
	location_message = ft_strjoin(file_name, " -> line:");
	tmp = location_message;
	location_message = strjoin_num(location_message, line_num);
	ft_putendl_fd(location_message, 2);
	free(tmp);
	free(location_message);
	perror(error_message);
	exit(EXIT_FAILURE);
}

/*
** perror_exit関数 + freeする関数
*/

void		free_perror_exit(char *ptr, char *error_message, int line_num, \
				char *file_name)
{
	free(ptr);
	perror_exit(error_message, line_num, file_name);
}

/*
** perror_exit関数 + 構造体の全てをfreeする関数
*/

void		all_free_perror_exit(t_minishell_info *info, char *error_message, \
					int line_num, char *file_name)
{
	size_t		i;

	// if (info == NULL)
		// signal_error_exit()
	i = 0;
	free(info->command);
	free(info->current_dir_path);
	i = 0;
	while (info->cmd_lst)
	{
		t_cmdlst *tmp;
		tmp = info->cmd_lst->next;
		while (info->cmd_lst->arg[i])
			i++;
		ptr_2d_free((void ***)&(info->cmd_lst->arg), i);
		free(info->cmd_lst);
		info->cmd_lst = tmp;
	}
	if (info->cmd_split != NULL)  // 先にNULL埋めておく
	{
		while (info->cmd_split[i])
			i++;
		ptr_2d_free((void ***)&(info->cmd_split), i);
	}
	if (errno == 0)
		exit(1);
	perror_exit(error_message, line_num, file_name);
}

void		all_free_minishell_info(t_minishell_info *info)
{
	size_t		i;

	i = 0;
	free(info->command);
	free(info->current_dir_path);
	i = 0;
	while (info->cmd_lst)
	{
		t_cmdlst *tmp;
		tmp = info->cmd_lst->next;
		while (info->cmd_lst->arg[i])
			i++;
		ptr_2d_free((void ***)&(info->cmd_lst->arg), i);
		free(info->cmd_lst);
		info->cmd_lst = tmp;
	}
	if (info->cmd_split != NULL)  // 先にNULL埋めておく
	{
		while (info->cmd_split[i])
			i++;
		ptr_2d_free((void ***)&(info->cmd_split), i);
	}
}

/*
** freeしてexitする関数
*/

void		free_exit(char **ptr, int state)
{
	ptr_free((void **)ptr);
	exit(state);
}

/*
** Ctrl +Dが押された時にfree_exitを使って抜ける関数
*/

void		ctrl_d_exit(char **ptr, t_minishell_info *info)
{
	ft_putstr_fd("\033[0Kexit\n", 2);
	free(info->command);
	free(info->current_dir_path);
	// free(info->cmd_lst);
	free_exit(ptr, EXIT_FAILURE);
}

/*
** error文シンタックスエラーを返して$?様に終了ステータスを入れる関数
*/

bool	syntax_error(int type, t_minishell_info *info)
{
	red_error();
	if (type == OUTPUT)
		write(2, SYNTAX_OP, 50);
	else if (type == DB_OUTPUT)
		write(2, SYNTAX_DB_OP, 51);
	else if (type == SEMICOLON)
		write(2, SYNTAX_SEMICOLON, 50);
	else if (type == PIPE)
		write(2, SYNTAX_PIPE, 50);
	else if (type == INPUT)
		write(2, SYNTAX_INPUT, 50);
	else if (type == SYNTAX_EOL_NUM)
		write(2, SYNTAX_EOL, 48);
	else if (type == NEWLINE)
		write(2, SYNTAX_NL, 56);
	else if (type == NOT_CMD)
		write(2, ERR_MANDATORY, 44);
	else if (type == DB_SEMICOLON)
		write(2, ERR_DB_SEMICOLON, 47);
	else if (type == DB_PIPE)
		write(2, ERR_DB_PIPE, 47);
	else if (type == OUTPUT_PIPE)
		write(2, ERR_OUTPUT_PIPE, 47);
	else if (type == DB_INPUT)
		write(2, ERR_DB_INPUT, 47);
	else if (type == TR_INPUT)
		write(2, ERR_TR_INPUT, 48);
	info->prev_rc = 258;
	return (false);
}

bool	syntax_warning(int type)
{
	yellow_warning();
	if (type == WARNING)
		write(2, ERR_MANDATORY, 44);
	return (false);
}

/*
** 関数
*/

bool	warning_message(char *error_message, t_minishell_info *info)
{
	yellow_warning();
	ft_putendl_fd(error_message, 2);
	errno = 0;
	all_free_perror_exit(info, NULL, 0, 0);
	return (false);
}


bool	two_ptr_2d_free_and_syntax_error(int type, char ***array, t_cmd_grp *cmd_grp_info, t_minishell_info *info)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while ((*array)[i])
			i++;
		ptr_2d_free((void ***)array, i);
	}
	i = 0;
	if (cmd_grp_info->cmd_grp != NULL)
		ptr_2d_free((void ***)cmd_grp_info->cmd_grp, cmd_grp_info->array_size);
	return (syntax_error(type, info));
}

bool	ptr_2d_free_and_syntax_error(int type, char ***cmd_grp, t_minishell_info *info)
{
	int	i;

	i = 0;
	if (cmd_grp != NULL)
	{
		while ((*cmd_grp)[i])
			i++;
		ptr_2d_free((void ***)cmd_grp, i);
	}
	return (syntax_error(type, info));
}
