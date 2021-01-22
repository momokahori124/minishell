/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 01:13:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/23 03:12:05 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

t_my_env	*my_env_lstlast(t_my_env *lst)
{
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_my_env	*make_my_env(char *env_name, char *env_value, t_minishell_info *info)
{
	t_my_env	*new;

	if (!(new = malloc(sizeof(t_my_env))))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (!(new->value = ft_strjoin(env_name, env_value)))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	new->next = NULL;
	return (new);
}


bool	is_in_env_and_update_if_any(t_my_env **my_env, char *env_name,
			char *env_value, t_minishell_info *info)
{
	extern char	**environ;
	size_t		i;
	int			j;

	i = 0;
	while (environ[i])
	{
		if (environ[i][0] == env_name[0] && !ft_strcmp(env_name, environ[i]))
		{
			j = 0;
			while (environ[i][j++] != '=')
				;
			j = -1;
			while (env_value[++j])
				environ[i][j] = env_value[j];
			return (true);
		}
		i++;
	}
	i = 0;
	while ((*my_env))
	{
		if ((*my_env)->value[0] == env_name[0] &&
				!ft_strcmp(env_name, (*my_env)->value))
		{
			if (!((*my_env)->value =
					re_strjoin(&((*my_env)->value), env_name, env_value)))
				all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
			return (true);
		}
		(*my_env) = (*my_env)->next;
	}
	(*my_env) = make_my_env(env_name, env_value, info);
	// 	printf("[%s]\n", (*my_env)->value);
	// 	(*my_env) = (*my_env)->next;
	// 	printf("[%p]\n", (*my_env));
	// (*my_env) = make_my_env(env_name, env_value, info);
	// 	printf("[%p]\n", (*my_env));
	return (true);
}

void	add_env_value(t_my_env **my_env, char *env_name, char *env_value,
							t_minishell_info *info)
{
	// t_my_env	*last;
	// char		*oldpwd;

	is_in_env_and_update_if_any(my_env, env_name, env_value, info);
		printf("[%p]\n", (*my_env));
	while (*my_env)
	{
	puts("2");
		printf("[%s]\n", (*my_env)->value);
		*my_env = (*my_env)->next;
	}
	is_in_env_and_update_if_any(my_env, "aaaaaaa", env_value, info);
	while (*my_env)
	{
	puts("3");
		printf("[%s]\n", (*my_env)->value);
		*my_env = (*my_env)->next;
	}
	exit(0);
	// if (!(oldpwd = ft_strjoin(env_name, env_value)))
	// 	all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	// if (!*begin)
	// {
	// 	(*begin)->value = ft_strjoin(env_name, env_value);
	// 	return ;
	// }
	// last = my_env_lstlast(*begin);
	// last->next = new;
}

static void	go_to_home(t_minishell_info *info)
{
	char		*cwd;

	puts("1");
	cwd = getcwd(NULL, 0);
	add_env_value(&(info->my_env), "OLDPWD=", cwd, info);
}

void	exec_cd(t_minishell_info *info, t_cmdlst *cmd)
{
	(void)cmd;
	// char	**arg;

	// arg = cmd->arg;
	// if (arg[1] == NULL ||
	// 	(arg[1] != NULL && arg[1][0] == '~' && arg[1][1] == '\0'))
go_to_home(info);
}
