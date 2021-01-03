/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_what.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:00:49 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/04 02:15:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/is_what.h"

bool	ispipe(int c)
{
	return (c == '|');
}

bool	isinput_redirect(int c)
{
	return (c == '<');
}

bool	isoutput_redirect(int c1, int c2)
{
	return (c1 == '>' && c2 != '>');
}

bool	isdouble_output_redirect(int c1, int c2)
{
	return (c1 == '>' && c2 == '>');
}

int		ispipe_or_redirect(int c1, int c2)
{
	if (isdouble_output_redirect(c1, c2))
		return (3);
	else if (isinput_redirect(c1) || isoutput_redirect(c1, c2))
		return (2);
	else if (ispipe(c1) || c1 == ';')
		return (1);
	else
		return (0);
}
