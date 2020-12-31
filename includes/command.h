/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:54 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/31 16:22:49 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "struct_etc.h"
# include "minishell.h"

char	*read_command_line(void);
bool	parse_command_line(t_minishell_info *info, char *envp[]);

bool	add_cmd_to_lst(t_minishell_info *info, char **command, int type);
void	exec_pwd(t_minishell_info *info);

char	*next_command(char *command);
void	cmd_lstadd_back(t_cmdlst **begin, t_cmdlst *new);
bool	rm_quotation(t_minishell_info *info);
bool	wait_pipe_or_redirect_next_cmd(t_minishell_info *info);


bool	execute_command(t_minishell_info *info);

char	**split_by_chrs_contain_delimiters(char *str, char *charset);

#endif
