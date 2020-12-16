/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:00 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/16 23:05:45 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe_redirect.h"

static bool	error_or_recursive(char buf, char *tmp, int cnt, \
		t_minishell_info *info)
{
	if (buf == '|')
	{
		if (tmp[0] == buf && cnt == 0)
			return (syntax_error(ERR_SYNTAX, "token `|\'", info));
		wait_next_cmd(info, 1);
	}
	return (true);
}

bool		wait_next_cmd(t_minishell_info *info, int cnt)
{
	int		rc;
	char	buf;
	char	*command_tmp;

	ft_putstr_fd("> ", 1);
	command_tmp = ft_strdup("");
	while ((rc = read(0, &buf, 1)) >= 0 && buf != '\n')
	{
		if (buf == '\n')
			ft_putstr_fd("> ", 1);
		if (rc != 0)
		{
			command_tmp = re_strjoinch(&command_tmp, ft_tolower(buf));
			if (error_or_recursive(buf, command_tmp, cnt, info) == false)
				return (false);
		}
		else if (command_tmp[0] == '\0' && buf != '\n')
			return (syntax_error(ERR_SYNTAX2, "end of file", info));
	}
	info->command = re_strjoin(&(info->command), command_tmp);
	ptr_free((void **)&command_tmp);
	if (rc == -1)
		all_free_perror_exit(info, ERR_READ);
	return (true);
}

static bool	check_next_cmd(char *command, t_minishell_info *info, int is_rc)
{
	if (*command || is_rc == 1)
	{
		if (is_rc == 1 && skip_space(command)[0] == '\0')
			return (wait_next_cmd(info, 0));
		else if (is_rc == 1 && ispipe(*command))
			return (error_message(ERR_MANDATORY, info));
		if (isdouble_output_redirect(*command, *(command + 1)))
			return (syntax_error(ERR_SYNTAX, "token `>>\'", info));
		else if (isoutput_redirect(*command, *(command + 1)) && \
				ispipe(*(command + 1)))
			return (syntax_error(ERR_SYNTAX, "token `>|\'", info));
		else if (isoutput_redirect(*command, *(command + 1)))
			return (syntax_error(ERR_SYNTAX, "token `>\'", info));
		else if (is_rc == 3 && ispipe(*command))
			return (syntax_error(ERR_SYNTAX, "token `|\'", info));
		else if (is_rc == 2 && ispipe(*command))
			return (syntax_error(ERR_SYNTAX, "token `newline\'", info));
		else if (isdouble_semicolon(*command, *(command + 1)))
			return (syntax_error(ERR_SYNTAX, "token `;;\'", info));
		else if (issemicolon(*command, *(command + 1)))
			return (syntax_error(ERR_SYNTAX, "token `;\'", info));
		else if (*command == ' ' && skip_space(command)[0] == '\0')
				return (syntax_error(ERR_SYNTAX, "token `newline\'", info));
		else
			return (true);
	}
	return (syntax_error(ERR_SYNTAX, "token `newline\'", info));
}

static bool	check_pipe_or_redirect(char *command, t_minishell_info *info)
{
	char			*tmp;
	int				is_rc;
	bool			return_value;
	unsigned int	i;

	return_value = true;
	i = 0;
	while (command[i])
	{
		is_rc = ispipe_or_redirect(command[i], *(command + i + 1));
		if (is_rc != 0)
		{
			int ttt = is_rc;
			if (is_rc >= 2)
				is_rc--;
			tmp = command + i + is_rc;
			// printf("[%s]\n", tmp);
			if ((return_value = check_next_cmd(tmp, info, ttt)) == false)
				return (false);
			command = info->command + i + is_rc;
			command = ft_strrchr(command, '|');
			if (command == NULL)
				break ;
		}
		i++;
	}
	return (return_value);
}

bool		wait_pipe_or_redirect_next_cmd(t_minishell_info *info)
{
	bool	rc;

	rc = true;
	rc = check_pipe_or_redirect(info->command, info);
	// (void)rc;
	// free(info->command);
	// free(info->current_dir_path);
	// exit(0);
	// printf("===[%s]\n", info->command);
	// printf("===[%d]\n", rc);
	// fflush(stdout);

	return (rc);
}