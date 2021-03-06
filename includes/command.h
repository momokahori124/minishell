/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:54 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/14 00:04:16 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "struct_etc.h"
# include "minishell.h"

char				*read_command_line(void);
bool				parse_command_line(t_minishell_info *info, char *envp[]);

bool				add_pwd_to_lst(t_minishell_info *info, char **command);
void				exec_pwd(t_minishell_info *info);

char				*next_command(char *command);
void				cmd_lstadd_back(t_cmdlst **begin, t_cmdlst *new);

bool				execute_command(t_minishell_info *info);

#endif
