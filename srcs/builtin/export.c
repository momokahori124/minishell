/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:56:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/24 23:54:28 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

void		exec_export(t_minishell_info *info, char **args)
{
	char		*env_name;
	int			i;
	int			j;

	if (args[1][0] == '-')
		return (error_mandatory(ERR_EXPORT, 30, info));
	j = 0;
	while (args[j + 1])
		j++;
	i = 0;
	while (args[j][i] != '=')
		i++;
	if (!(env_name = malloc(i + 1)))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = -1;
	while (args[j][++i] != '=')
		env_name[i] = args[j][i];
	env_name[i] = '\0';
	update_env_value(&(info->env), env_name, args[j] + i, info);
	ptr_free((void **)&env_name);
}
