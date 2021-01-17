/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 22:39:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/18 02:49:22 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

/*
** parseする時に(add_pwd_to_lst等)、コマンドを'|'とか'>>'とかまで持っていく
** 見つからなかった場合はもうコマンドとして終わりなのでreturn ("");する
*/

// char	*next_command(char *command)
// {
// 	size_t	i;

// 	i = 0;
// 	while (command[i])
// 	{
// 		if (command[i] == '>' && command[i + 1] == '>')
// 			return (command + i + 1);
// 		else if (command[i] == ';' || command[i] == '|' ||
// 			command[i] == '<' || command[i] == '>')
// 			return (command + i);
// 		i++;
// 	}
// 	return ("");
// }

static t_cmdlst	*cmd_lstlast(t_cmdlst *lst)
{
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

/*
** parseする時に(add_pwd_to_lst等)、後ろにリストをつなげる関数
*/

void	cmd_lstadd_back(t_cmdlst **begin, t_cmdlst *new)
{
	t_cmdlst *last;

	if (!*begin)
	{
		*begin = new;
		return ;
	}
	last = cmd_lstlast(*begin);
	last->next = new;
}

void	rm_chr_in_str(char **str, char chr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != chr)
		{
			(*str)[j] = (*str)[i];
			j++;
		}
		i++;
	}
	(*str)[j] = '\0';
}

ssize_t		safe_read(char *buf, char **ptr, t_minishell_info *info)
{
	ssize_t	rc;

	rc = read(0, buf, 1);
	if (rc < 0)
	{
		ptr_free((void**)ptr);
		all_free_perror_exit(info, ERR_READ, __LINE__, __FILE__);
	}
	return (rc);
}
