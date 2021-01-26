/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 02:53:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cute_message.h"

void		put_prompt(t_minishell_info *info)
{
	if (write(1, g_user_name, g_user_name_count) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(1, "\033[1m\x1b[35m ❤️ \x1b[0m", 21) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(1, g_working_dir, g_working_dir_count) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(1, "\033[1m\x1b[35m ❤️ > \x1b[0m", 23) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}