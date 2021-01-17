/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 03:54:12 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/17 23:37:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cute_message.h"

/*
** ほりももちゃんが作ったput系の関数群
** writeを何回も呼ぶの嫌だったのでput_welcome_messageみたいにするか迷い中。
*/

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
// 			return (pwd + i + 1);
// 		i--;
// 	}
// 	return (pwd);
// }

void		put_prompt(t_minishell_info *info)
{
	if (ft_putstr_fd(g_user_name, 1) == false)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(1, "\033[1m\x1b[35m ❤️ \x1b[0m", 21) < 0)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(g_working_dir, 1) == false)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
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
	write(STDERR_FILENO, message, len + 31);
	ptr_free((void **)&message);
	return (CMD_NOT_FOUND);
}
