/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_what.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:43:10 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/16 22:44:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_WHAT_H
# define IS_WHAT_H

# include "minishell.h"

bool	ispipe(int c);
bool	isinput_redirect(int c);
bool	isoutput_redirect(int c1, int c2);
bool	isdouble_output_redirect(int c1, int c2);
int		ispipe_or_redirect(int c1, int c2);
bool	isdouble_semicolon(int c1, int c2);
bool	issemicolon(int c1, int c2);

#endif
