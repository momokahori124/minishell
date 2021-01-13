/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_format_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 01:37:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/14 03:16:07 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

static bool	free_and_syntax_error(int type, char ***cmd_grp, t_minishell_info *info)
{
	int	i;

	i = 0;
	if (cmd_grp != NULL)
	{
		while ((*cmd_grp)[i])
			i++;
		printf("i : %d\n", i);
		ptr_2d_free((void ***)cmd_grp, i);
	}
	return (syntax_error(type, info));
}

bool	check_format_of_command(char ***grp, t_minishell_info *info)
{
	int	i;

	i = 0;
	while ((*grp)[i])
	{
		printf("grp[i] : %s\n", (*grp)[i]);
		if (i != 0 && (*grp)[i][0] == '|' && (*grp)[i][1] != '|' && !(*grp)[i + 1])
		{
			if ((*grp = wait_for_next_cmd(grp, i + 1, info)) == NULL)
				return (false);
			break ;
		}
		// else if ((*grp)[0][0] == '|' && (*grp)[0][1] == '|' && !(*grp)[i + 1])
		// 	return (free_and_syntax_error(NOT_CMD, grp, info));
		// else if ((*grp)[0][0] == '|' && !(*grp)[1])
		// 	return (free_and_syntax_error(PIPE, grp, info));
		// else if ((*grp)[0][0] == ';' && !(*grp)[1])
		// 	return (free_and_syntax_error(SEMICOLON, grp, info));
		// else if ((*grp)[i][0] == ';' && (*grp)[i][1] == ';')
		// 	return (free_and_syntax_error(DB_SEMICOLON, grp, info));
		// else if ((*grp)[i][0] == '<' && (*grp)[i][1] == '<')
		// 	return (free_and_syntax_error(NOT_CMD, grp, info));

		// if ((*grp)[i][0] == '<' && !(*grp)[i + 1])
		// 	return (free_and_syntax_error(NEWLINE, grp, info));

		if (is_output_format_error(grp, i, info) == false)
			return (false);



		// else if (i == 0 && !(*grp)[i + 1] && (*grp)[i][0] == '<' && (*grp)[i][1] == '<')
		// 	return (free_and_syntax_error(NOT_CMD, grp, info));
		// else if (i == 0 && !(*grp)[i + 1] && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<'))
		// 	return (free_and_syntax_error(NEWLINE, grp, info));
		// else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '>' && (*grp)[i - 1][1] == '>')
		// 	return (free_and_syntax_error(DB_OUTPUT, grp, info));
		// else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '>' && (*grp)[i - 1][1] == '|')
		// 	return (free_and_syntax_error(NOT_CMD, grp, info));
		// else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '>' && (*grp)[i - 1][1] != '>')
		// 	return (free_and_syntax_error(OUTPUT, grp, info));
		// else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == ';' && (*grp)[i - 1][1] == ';')
		// 	return (free_and_syntax_error(NOT_CMD, grp, info));
		// else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == ';' && (*grp)[i - 1][1] != ';')
		// 	return (free_and_syntax_error(SEMICOLON, grp, info));
		// else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '|' && (*grp)[i - 1][1] == '|')
		// 	return (free_and_syntax_error(PIPE, grp, info));
		// else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '|' && (*grp)[i - 1][1] != '|')
		// 	return (free_and_syntax_error(NOT_CMD, grp, info));
		// else if (i != 0 && ((*grp)[i][0] == '>' || (*grp)[i][0] == '<') && (*grp)[i - 1][0] == '<' && (*grp)[i - 1][1] == '<')
		// 	return (free_and_syntax_error(NOT_CMD, grp, info));
		i++;
	}
	return (true);
}
