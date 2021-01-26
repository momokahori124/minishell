/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:58:39 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 02:53:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_env(t_minishell_info *info)
{
	t_envlst	*begin;
	t_envlst	*next;
	size_t		i;
	extern char	**environ;

	if (!(begin = malloc(sizeof(t_envlst))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	begin->value = ft_strdup(environ[0]);
	begin->next = NULL;
	info->env = begin;
	i = 1;
	while (environ[i])
	{
		if (!(next = malloc(sizeof(t_envlst))))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		next->value = ft_strdup(environ[i]);
		next->next = NULL;
		begin->next = next;
		begin = next;
		i++;
	}
}
