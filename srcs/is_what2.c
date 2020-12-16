/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_what2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:42:45 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/16 22:44:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/is_what.h"

bool	isdouble_semicolon(int c1, int c2)
{
	return (c1 == ';' && c2 == ';');
}

bool	issemicolon(int c1, int c2)
{
	return (c1 == ';' && c2 != ';');
}
