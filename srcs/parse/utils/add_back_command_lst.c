/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_command_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:27:50 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/25 16:44:49 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/command.h"

void		add_back_command_lst(t_minishell_info *info, char **command, int type)
{
	t_cmdlst	*cmd;

	if (!(cmd = malloc(sizeof(t_cmdlst))))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (type == CMD_NUM)
		cmd->type = NOT_CMD;
	else if (type == OUTPUT_PIPE)
		cmd->type = OUTPUT;
	else
		cmd->type = type;
	cmd->arg = command;
	cmd->next = NULL;
	cmd_lstadd_back(&(info->cmd_lst), cmd);
}
