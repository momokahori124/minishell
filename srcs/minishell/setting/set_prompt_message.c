/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt_message.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:50:40 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 04:00:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_prompt_message(char *envp[], t_envlst *env_lst)
{
	char *s;
	(void)envp;

	s = search_env("USER", 4, env_lst);
	g_user_name = s;
	g_user_name_count = 0;
	while (g_user_name[g_user_name_count])
		g_user_name_count++;
	// s = get_working_dir(envp[search_env(envp, "PWD")]);
	s = search_env("PWD", 3, env_lst);
	printf("[%s]\n", s);
	g_working_dir = s;
	printf("[%s]\n", g_working_dir);
	g_working_dir_count = 0;
	while (g_working_dir[g_working_dir_count])
		g_working_dir_count++;
}
