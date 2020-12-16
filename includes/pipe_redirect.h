/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:45 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/16 22:43:57 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_REDIRECT_H
# define  PIPE_REDIRECT_H

# include "minishell.h"

bool		wait_pipe_or_redirect_next_cmd(t_minishell_info *info);
bool		wait_next_cmd(t_minishell_info *info, int cnt);

#endif
