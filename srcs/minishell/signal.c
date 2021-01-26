/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:50:53 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 03:07:21 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signal.h"

/*
** このファイルにある関数はコピペなので無視で良い
** Ctrl + C や Ctrl + Dを押した時の処理を書いてるだけ
*/

void	sig_quit(int code)
{
	if (g_signal.fork_pid == 0)
		write(STDERR_FILENO, "\b\b  \b\b", 6);
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
		write(STDERR_FILENO, "\b\b  \n", 5);
		put_prompt(NULL);
		g_signal.exit_status = 1;
	}
	else
	{
		write(STDERR_FILENO, "\b\b  \n", 5);
		g_signal.exit_status = 130;
	}
	exit(1);
	g_signal.fork_pid = 0;
	// g_signal.sigint = 1;
}