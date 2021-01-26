/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_welcome_message.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:38:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 00:39:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cute_message.h"

void	display_welcome_message(void)
{
	write(STDOUT_FILENO, "\n\n\033[1m\x1b[35m❤️ ❤️ ❤️ Welcome to minishell ❤️ ❤️ ❤️\x1b[0m\n\n\
This is my own little bash written by C. \n\
A student project at 42tokyo.\n\
Run 'help' for information on a command.\n\n", 193);
}
