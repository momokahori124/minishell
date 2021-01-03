/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:51:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/04 00:31:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"
# include "struct_etc.h"
# define ERR_READ "Failed to read at the above location. "
# define ERR_MALLOC "Failed to malloc at the above location. "
# define ERR_EXECVE "Failed to execve at the above location. "
# define ERR_SYNTAX "minishell: syntax error near unexpected "
# define ERR_SYNTAX2 "minishell: syntax error: unexpected "
# define ERR_MANDATORY "That command is not supported by mandatory."


void	perror_exit(char *error_message, int line_num, char *file_name);
void	free_perror_exit(char *ptr, char *error_message, int line_num, \
				char *file_name);
void	free_exit(char *ptr, int state);
void	all_free_perror_exit(t_minishell_info *info, char *error_message, \
				int line_num, char *file_name);

void	ctrl_d_exit(char *ptr);
bool	syntax_error(char *error_message, char *word, t_minishell_info *info);
bool	error_message(char *error_message, t_minishell_info *info);

#endif
