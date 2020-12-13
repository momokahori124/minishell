/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:04:00 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/14 00:18:55 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../utils/Libft/includes/libft.h"
# include "error.h"
# include "minishell_utils.h"
# include "color.h"
# include "command.h"
// # include "struct_etc.h"
// # include "command_pwd.h"
# include "cute_message.h"
# include "signal.h"
# define MAX(x, y) ((x) > (y) ? (x) : (y))
# define SUCCESS 0
# define ERROR 1
# define STDOUT 1

// typedef struct		s_minishell_info
// {
// 	char			*command;
// 	char			*current_dir_path;
// 	struct s_cmdlst	*cmd_lst;
// }					t_minishell_info;

int			search_env(char *envp[], char *env_name);
void		ft_putenv(char *s);

#endif
