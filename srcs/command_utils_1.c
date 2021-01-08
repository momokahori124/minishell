/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 22:39:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/08 01:25:12 by tjinichi         ###   ########.fr       */
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
		if (command[i] == '>' && command[i + 1] == '>')
			return (command + i + 1);
		else if (command[i] == ';' || command[i] == '|' || \
			command[i] == '<' || command[i] == '>')
			return (command + i);
		i++;
	}
	return ("");
}

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

// static bool wait_quotation(char first_appear, t_minishell_info *info)
// {
// 	int		rc;
// 	char	buf;

// 	ft_putstr_fd("> ", 1);
// 	info->command = re_strjoinch(&(info->command), '\n');
// 	if (info->command == NULL)
// 		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	while ((rc = read(0, &buf, 1)) > 0)
// 	{
// 		if (buf == '\n')
// 			ft_putstr_fd("> ", 1);
// 		if (buf == first_appear)
// 			break ;
// 		info->command = re_strjoinch(&(info->command), buf);
// 		if (info->command == NULL)
// 			all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	}
// 	if (rc == 0)
// 	{
// 		ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 1);
// 		ft_putchar_fd(first_appear, 1);
// 		ft_putstr_fd("`", 1);
// 		ft_putstr_fd("\nminishell: syntax error: unexpected end of file", 1);
// 		return (true);
// 	}
// 	// info->prev_rc = put_cmd_not_found(info->command);
// 	return (true);
// }

// static void	removing(t_minishell_info *info, char first_appear)
// {
// 	char		*new;
// 	size_t		i;
// 	size_t		j;

// 	if (!(new = malloc(sizeof(char) * (ft_strlen(info->command)))))
// 		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	i = 0;
// 	j = 0;
// 	while ((info->command)[i])
// 	{
// 		if ((info->command)[i] != first_appear)
// 		{
// 			new[j] = (info->command)[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new[j] = '\0';
// 	ptr_free((void **)&(info->command));
// 	info->command = new;
// }

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
