/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/18 04:19:17 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_REDIRECT_H
# define  PIPE_REDIRECT_H

# include "minishell.h"

t_cmdlst	*redirect_sep(t_minishell_info *info, t_cmdlst **cmd_lst);

#endif
