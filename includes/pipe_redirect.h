/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/19 21:03:02 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_REDIRECT_H
# define  PIPE_REDIRECT_H

# include "minishell.h"

t_cmdlst	*redirect_sep(t_minishell_info *info, t_cmdlst **cmd_lst);
t_cmdlst	*pipe_sep(t_minishell_info *info, t_cmdlst **cmd_lst);
void		connect_std_in_out_and_pipe(int pipefd[2], int i_o,
					t_minishell_info *info);
void		close_pipe_fd(int pipefd[2], t_minishell_info *info);

#endif
