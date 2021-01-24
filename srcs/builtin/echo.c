/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:04:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/25 01:08:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

void		exec_echo(t_minishell_info *info, char **args)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	if (args[1][0] == '-')
		if ((n_flag = 1) && ft_strcmp(args[1], "-n") != 0)
			return (error_mandatory(ERR_ECHO, 21, info));
	i = 1 + n_flag;
	while (args[i])
	{
		if (ft_putstr_fd(args[i], 1) == false)
			all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (args[i + 1] == NULL && n_flag == 0)
		{
			if (write(1, " \n", 2) == -1)
				all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		else
		{
			if (write(1, " ", 1) == -1)
				all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		i++;
	}
}
