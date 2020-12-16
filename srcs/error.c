/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:50:48 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/17 00:12:44 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"

/*
** Errorを赤文字(\033[31m)・太文字(\033[1m)で出す関数
*/

void	red_error(void)
{
	write(1, "\033[31m\033[1m[Error]\033[0m\n", 21);
}

void	yellow_warning(void)
{
	write(1, "\033[33m\033[1m[Warning]\033[0m\n", 23);
}

/*
** エラーメッセージとエラーが起きた場所をを出力してexitする関数。
*/

void		perror_exit(char *error_message)
{
	char	*location_message;
	char	*tmp;

	red_error();
	location_message = ft_strjoin(__FILE__, " -> line:");
	tmp = location_message;
	location_message = strjoin_num(location_message, __LINE__);
	ft_putendl_fd(location_message, 1);
	free(tmp);
	free(location_message);
	perror(error_message);
	exit(EXIT_FAILURE);
}

/*
** perror_exit関数 + freeする関数
*/

void		free_perror_exit(char *ptr, char *error_message)
{
	free(ptr);
	perror_exit(error_message);
}

/*
** perror_exit関数 + 構造体の全てをfreeする関数
*/

void		all_free_perror_exit(t_minishell_info *info, char *error_message)
{
	free(info->command);
	free(info->current_dir_path);
	free(info->cmd_lst);
	perror_exit(error_message);
}

/*
** freeしてexitする関数
*/

void		free_exit(char *ptr, int state)
{
	free(ptr);
	exit(state);
}

/*
** Ctrl +Dが押された時にfree_exitを使って抜ける関数
*/

void		ctrl_d_exit(char *ptr)
{
	ft_putstr_fd("\033[0Kexit\n", 1);
	free_exit(ptr, EXIT_FAILURE);
}

/*
** error文シンタックスエラーを返して$?様に終了ステータスを入れる関数
*/

bool	syntax_error(char *error_message, char *word, t_minishell_info *info)
{
	red_error();
	ft_putstr_fd(error_message, 2);
	ft_putendl_fd(word, 2);
	info->prev_rc = 258;
	return (false);
}

/*
** error文シンタックスエラーを返して$?様に終了ステータスを入れる関数
*/

bool	error_message(char *error_message, t_minishell_info *info)
{
	yellow_warning();
	ft_putendl_fd(error_message, 2);
	info->prev_rc = 258;
	return (false);
}
