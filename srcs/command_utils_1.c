/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 22:39:58 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/31 16:17:25 by tjinichi         ###   ########.fr       */
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

static bool wait_quotation(char first_appear, t_minishell_info *info)
{
	int		rc;
	char	buf;

	ft_putstr_fd("> ", 1);
	info->command = re_strjoinch(&(info->command), '\n');
	if (info->command == NULL)
		all_free_perror_exit(info, ERR_MALLOC);
	while ((rc = read(0, &buf, 1)) > 0)
	{
		if (buf == '\n')
			ft_putstr_fd("> ", 1);
		if (buf == first_appear)
			break ;
		info->command = re_strjoinch(&(info->command), buf);
		if (info->command == NULL)
			all_free_perror_exit(info, ERR_MALLOC);
	}
	if (rc == 0 && buf != '\n')
	{
		// minishell:にする
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 1);
		ft_putchar_fd(first_appear, 1);
		ft_putendl_fd("\'", 1);
	}
	return (true);
}

static void	removing(t_minishell_info *info, char first_appear)
{
	char		*new;
	unsigned int	i;
	unsigned int	j;

	if (!(new = malloc(sizeof(char) * (ft_strlen(info->command)))))
		all_free_perror_exit(info, ERR_MALLOC);
	i = 0;
	j = 0;
	while ((info->command)[i])
	{
		if ((info->command)[i] != first_appear)
		{
			new[j] = (info->command)[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	ptr_free((void **)&(info->command));
	info->command = new;
}

static bool	check_quotation(char *command, t_minishell_info *info)
{
	unsigned int	single_quo;
	unsigned int	double_quo;
	char			first_appear;
	bool			rc;

	single_quo = 0;
	double_quo = 0;
	first_appear = '\0';
	rc = true;
	while (*command)
	{
		if (first_appear == '\0' && isquotation(*command))
			first_appear = *command;
		if (issingle_quotation(*command))
			single_quo++;
		if (isdouble_quotation(*command))
			double_quo++;
		command++;
	}
	if ((single_quo & 1) == 1 || (double_quo & 1) == 1)
	{
		rc = wait_quotation(first_appear, info);
		removing(info, first_appear);
	}
	return (rc);
}

bool		rm_quotation(t_minishell_info *info)
{
	bool	rc;

	rc = true;
	rc = check_quotation(info->command, info);
	// if (rc == false)
	// 	*command = info->command;
	// else
	// 	;
	return (rc);
}
