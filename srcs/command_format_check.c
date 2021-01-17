/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_format_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 01:37:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/16 16:40:20 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

bool	check_format_of_command(char ***grp, t_minishell_info *info)
{
	int	i;

	i = -1;
	while ((*grp)[++i])
	{
		if (i != 0 && (*grp)[i][0] == '|' && (*grp)[i][1] != '|' && !(*grp)[i + 1])
		{
			wait_for_next_cmd(grp, i + 1, info);
			if (*grp == NULL)
				return (false);
			break ;
		}
		if (is_output_format_error(grp, i, info) == false)
			return (false);
		if (is_pipe_format_error(grp, i, info) == false)
			return (false);
		if (is_semicolon_format_error(grp, i, info) == false)
			return (false);
	}
	return (true);
}
