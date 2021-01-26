/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alloc_ptr_in_cmd_lst.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:36:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 01:39:56 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipe_redirect.h"

void	free_alloc_ptr_in_cmd_lst(t_cmdlst **cmd_lst)
{
	if ((*cmd_lst)->arg != NULL)
		ptr_2d_free((void ***)&((*cmd_lst)->arg), ARG_MAX);
	ptr_free((void **)cmd_lst);
}