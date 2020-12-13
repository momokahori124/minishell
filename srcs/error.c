/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:50:48 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/14 00:10:43 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"

/*
** Errorを赤文字(\033[31m)・太文字(\033[1m)で出す関数
*/

static void	red_error(void)
{
	write(1, "\033[31m\033[1m[Error]\033[0m\n", 21);
}

/*
** エラーメッセージとエラーが起きた場所をを出力してexitする関数。
*/

void		perror_exit(char *error_message, int state)
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
	exit(state);
}

/*
** perror_exit関数 + freeする関数
*/

void		free_perror_exit(char *ptr, char *error_message, int state)
{
	free(ptr);
	perror_exit(error_message, state);
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
