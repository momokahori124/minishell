/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:04:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 19:19:35 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <dirent.h>
# include "../utils/Libft/includes/libft.h"
# include "error.h"
# include "minishell_utils.h"
# include "color.h"
# include "command.h"
# include "struct_etc.h"
// # include "command_pwd.h"
# include "cute_message.h"
# include "signal.h"
# include "is_what.h"
# define MAX(x, y) ((x) > (y) ? (x) : (y))
# define SUCCESS 0
# define ERROR 1
// # define STDOUT 1

char	*search_env(char *str, int num, t_envlst *env_lst);
// void	ft_putenv(char *s, t_minishell_info *info);
void	set_minishell_info(t_minishell_info *info);
void	set_prompt_message(t_envlst *env_lst);
void	set_shell_level(void);
void	set_env(t_minishell_info *info);

#endif
