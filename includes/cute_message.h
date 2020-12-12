/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_message.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 03:55:09 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/12 04:00:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUTE_MESSAGE_H
# define CUTE_MESSAGE_H

# include "minishell.h"

void		put_prompt(char *envp[]);
void		put_welcome_message(void);
void		put_help_message(void);
void		put_cmd_not_found(char *line);

#endif
