/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:50:53 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/05 21:28:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signal.h"

/*
** このファイルにある関数はコピペなので無視で良い
** Ctrl + C や Ctrl + Dを押した時の処理を書いてるだけ
*/

# define STDERR 2

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

t_sig	g_sig;

void	sig_quit(int code)
{
	exit(1);
	(void)code;
}

void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0) //子だったら
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", STDERR);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.exit_status = 130;
	}
	exit(0);
	g_sig.sigint = 1;
}
