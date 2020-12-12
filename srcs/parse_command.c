/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:27 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/13 03:54:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

char		*read_command_line(void)
{
	char	*command;
	char	buf;
	ssize_t	rc;

	command = ft_strdup("");
	while ((rc = read(0, &buf, 1)) >= 0 && buf != '\n')
	{
		if (rc != 0)
			command = re_strjoinch(&command, buf);
		else
		{
			if (command[0] == '\0')
			{
				ft_putstr_fd("\033[0Kexit\n", 1);
				free_exit(command, EXIT_SUCCESS);
			}
			write(0, "\033[0K", 4);
		}
	}
	if (rc == -1)
		free_perror_exit(command, ERR_READ, EXIT_FAILURE);
	return (command);
}
