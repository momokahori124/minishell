/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 22:39:58 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/14 00:38:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

/*
** parseする時に(add_pwd_to_lst等)、コマンドを'|'とか'>>'とかまで持っていく
** 見つからなかった場合はもうコマンドとして終わりなのでreturn ("");する
*/

char	*next_command(char *command)
{
	size_t	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == ';' || \
				(command[i] == '>' && command[i + 1] == '>'))
			return (command + i + 1);
		else if (command[i] == '|' || command[i] == '<' || \
					command[i] == '>')
			return (command + i);
		i++;
	}
	return ("");
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
