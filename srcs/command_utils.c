/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 22:39:58 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/14 00:14:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

/*
** parseする時に(add_pwd_to_lst等)、コマンドを'|'とか'>>'とかまで持っていく
** まだ'|'しか対応してない。
** 見つからなかった場合はもうコマンドとして終わりなのでreturn ("");する
*/

char	*next_command(char *command)
{
	char	*res;

	res = ft_strchr(command, '|');
	if (res == NULL)
		return ("");
	return (res);
}

/*
** parseする時に(add_pwd_to_lst等)、後ろにリストをつなげる関数
*/

void	cmd_lstadd_back(t_cmdlst **begin, t_cmdlst *new)
{
	if (!*begin)
	{
		*begin = new;
		return ;
	}
	while (*begin)
		*begin = (*begin)->next;
	*begin = new;
}
