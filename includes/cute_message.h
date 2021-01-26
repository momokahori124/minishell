/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_message.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 03:55:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 00:39:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUTE_MESSAGE_H
# define CUTE_MESSAGE_H

# include "minishell.h"
# define CMD_NOT_FOUND 127

void		put_prompt(t_minishell_info *info);
void		display_welcome_message(void);
void		put_help_message(void);
// int			put_cmd_not_found(char **line);
// void		put_cmd_not_found(char *command);

#endif
