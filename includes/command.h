/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:54 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/14 20:35:02 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "struct_etc.h"
# include "minishell.h"
# include "exit.h"

// char	*read_command_line(t_minishell_info *info);
bool	read_command_line(t_minishell_info *info);
bool	parse_command_line(t_minishell_info *info);

bool	add_cmd_to_lst(t_minishell_info *info, char **command, int type);
void	exec_pwd(t_minishell_info *info);

char	*next_command(char *command);
void	cmd_lstadd_back(t_cmdlst **begin, t_cmdlst *new);

void	rm_chr_in_str(char **str, char chr);
ssize_t	safe_read(char *buf, char **ptr, t_minishell_info *info);

bool	rm_quotation(t_minishell_info *info);
bool	wait_quotation(char first_appear, char **command, t_minishell_info *info);

// char		**wait_for_next_cmd(char ***cmd_grp, int array_size, t_minishell_info *info);
bool	wait_for_next_cmd(char ***cmd_grp, int array_size, t_minishell_info *info);


bool	execute_command(t_minishell_info *info);

// utils2
char	**split_by_chrs_contain_delimiters(char *str, char *charset);

// utils3
char		**rm_space_in_array(char **arr, t_minishell_info *info);

// format
bool	check_format_of_command(char ***grp, t_minishell_info *info);

//is_out
bool	is_output_format_error(char ***grp, int i, t_minishell_info *info);

//is_pipe
bool	is_pipe_format_error(char ***grp, int i, t_minishell_info *info);

//is_semi
bool		is_semicolon_format_error(char ***grp, int i, \
				t_minishell_info *info);

#endif
