/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:00:36 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/12 03:59:31 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_utils.h"

// static char		*get_working_dir(char *pwd)
// {
// 	int len = ft_strlen(pwd);
// 	int i = len - 1;
// 	char *ret;
// 	int count = 0;

// 	while (i >= 0)
// 	{
// 		if (pwd[i] == '/')
// 			count++;
// 		if (count == 2)
// 		{
// 			ret = ft_strdup(pwd + i + 1);
// 			return (ret);
// 		}
// 		i--;
// 	}
// 	ret = ft_strdup(pwd);
// 	return (ret);
// }

// void		put_prompt(char *envp[])
// {
// 	char *s;

// 	s = envp[search_env(envp, "USER")];
// 	ft_putenv(s);
// 	ft_putstr_fd("\x1b[35m ❤️ \x1b[0m", 1);
// 	s = get_working_dir(envp[search_env(envp, "PWD")]);
// 	ft_putstr_fd(s, 1);
// 	free(s);
// 	ft_putstr_fd("\x1b[35m ❤️ > \x1b[0m", 1);
// }

// void	put_welcome_message(void)
// {
// 	ft_putstr_fd("\n\n\x1b[35m❤️ ❤️ ❤️ Welcome to minishell ❤️ ❤️ ❤️\x1b[0m\n\n
// This is my own little bash written by C. \n
// A student project at 42tokyo.\n
// Run 'help' for information on a command.\n\n", 1);
// }

// void	put_help_message(void)
// {
// 	ft_putstr_fd("\n================================\n", 1);
// 	ft_putstr_fd("Usage : this is usage of this shell\n\n", 1);
// 	ft_putstr_fd("     pwd\n", 1);
// 	ft_putstr_fd("     env\n", 1);
// 	ft_putstr_fd("     exit\n", 1);
// 	ft_putstr_fd("\n================================\n\n", 1);
// }
