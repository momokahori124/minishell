/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:11:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 19:05:04 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/command.h"

void	error_mandatory(char *err_message, int num, t_minishell_info *info)
{
	red_error();
	if (write(STDERR_FILENO, err_message, num) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return ;
}
