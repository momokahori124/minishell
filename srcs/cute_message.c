/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 03:54:12 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/08 00:50:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cute_message.h"

/*
** ほりももちゃんが作ったput系の関数群
** writeを何回も呼ぶの嫌だったのでput_welcome_messageみたいにするか迷い中。
*/

static char		*get_working_dir(char *pwd)
{
	int len = ft_strlen(pwd);
	int i = len - 1;
	char *ret;
	int count = 0;

	while (i >= 0)
	{
		if (pwd[i] == '/')
			count++;
		if (count == 2)
		{
			ret = ft_strdup(pwd + i + 1);
			return (ret);
		}
		i--;
	}
	ret = ft_strdup(pwd);
	return (ret);
}

void		put_prompt(char *envp[], t_minishell_info *info)
{
	char *s;

	s = envp[search_env(envp, "USER")];
	ft_putenv(s, info);
	if (write(1, "\033[1m\x1b[35m ❤️ \x1b[0m", 21) < 0)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	s = get_working_dir(envp[search_env(envp, "PWD")]);
	if (ft_putstr_fd(s, 1) == false)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	free(s);
	if (write(1, "\033[1m\x1b[35m ❤️ > \x1b[0m", 23) < 0)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

void	put_welcome_message(void)
{
	ft_putstr_fd("\n\n\033[1m\x1b[35m❤️ ❤️ ❤️ Welcome to minishell ❤️ ❤️ ❤️\x1b[0m\n\n\
This is my own little bash written by C. \n\
A student project at 42tokyo.\n\
Run 'help' for information on a command.\n\n", 1);
}

void	put_help_message(void)
{
	ft_putstr_fd("\n================================\n", 1);
	ft_putstr_fd("Usage : this is usage of this shell\n\n", 1);
	ft_putstr_fd("     pwd\n", 1);
	ft_putstr_fd("     env\n", 1);
	ft_putstr_fd("     exit\n", 1);
	ft_putstr_fd("\n================================\n\n", 1);
}

int		put_cmd_not_found(char *command)
{
	char	*message;
	size_t	len;

	len = ft_strlen(command);
	message = ft_str3join("minishell: ", command, ": command not found\n");
	write(STDOUT, message, len + 31);
	ptr_free((void **)&message);
	return (CMD_NOT_FOUND);
}
