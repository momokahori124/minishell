/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:50:53 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/24 21:50:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signal.h"

/*
** このファイルにある関数はコピペなので無視で良い
** Ctrl + C や Ctrl + Dを押した時の処理を書いてるだけ
*/

# define STDERR 2

// typedef struct	s_sig
// {
// 	int				sigint;
// 	int				sigquit;
// 	int				exit_status;
// 	pid_t			pid;
// }				t_sig;

// t_sig	g_sig;

void	sig_quit(int code)
{
	if (g_signal.fork_pid == 0)
		ft_putstr_fd("\b\b  \b\b", STDERR);
	else
	{
		printf("Quit: %d\n", code);
		g_signal.exit_status = 131;
	}
}

void	sig_int(int code)
{
	(void)code;
	if (g_signal.fork_pid == 0) //子だったら
	{
		write(1, "\b\b  \n", 5);
		put_prompt(NULL);
		g_signal.exit_status = 1;
	}
	else
	{
		write(1, "\b\b  \n", 5);
		g_signal.exit_status = 130;
	}
	exit(1);
	g_signal.fork_pid = 0;
	// g_signal.sigint = 1;
}
