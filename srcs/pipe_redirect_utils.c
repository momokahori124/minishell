/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/04 22:46:13 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe_redirect.h"

/*
** "pwd|"の後に"|"を打つとエラーで"aaa|"を打つと続行なのでこんな再帰を使ってる
** もしかしたらもっとわかりやすいやり方あるかも
*/

static bool	error_or_recursive(char buf, char *tmp, int cnt, \
		t_minishell_info *info)
{
	if (buf == '|')
	{
		if (tmp[0] == buf && cnt == 0)
			return (syntax_error(PIPE, info));
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
		write(0, "\033[0K", 4);
		if (rc != 0)
		{
			command_tmp = re_strjoinch(&command_tmp, ft_tolower(buf));
			if (error_or_recursive(buf, command_tmp, cnt, info) == false)
				return (false);
		}
		else if (command_tmp[0] == '\0' && buf != '\n')
			return (syntax_error(SYNTAX_EOL_NUM, info));
	}
	info->command = re_strjoin(&(info->command), command_tmp);
	ptr_free((void **)&command_tmp);
	if (rc == -1)
		all_free_perror_exit(info, ERR_READ, __LINE__, __FILE__);
	return (true);
}

bool	check_double_semicolon_error(int separator_count, int type, \
			t_minishell_info *info)
{
	if (separator_count == 1 || separator_count == 2)
		return (syntax_error(NOT_CMD, info));
	else if (separator_count == 3)
		return (syntax_error(type, info));
	else
	{
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
	}
	return (true);
}

bool	check_single_semicolon_error(int separator_count, int type, \
			t_minishell_info *info)
{
	if (separator_count == 1 || separator_count == 2)
		return (syntax_error(SEMICOLON, info));
	else if (separator_count == 3)
		return (syntax_error(type, info));
	else
	{
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
	}
	return (true);
}

bool	check_double_pipe_error(int separator_count, int type, \
			t_minishell_info *info)
{
	if (separator_count == 1)
		return (syntax_error(PIPE, info));
	else if (separator_count == 2 || separator_count == 3)
		return (syntax_error(NOT_CMD, info));
	else
	{
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
	}
	return (true);
}

bool	check_single_pipe_error(int separator_count, int type, \
			t_minishell_info *info)
{
	if (separator_count == 1)
		// return (true);
		return (syntax_warning(WARNING));
	else if (separator_count == 2)
		return (syntax_error(PIPE, info));
	else if (separator_count == 3)
		return (syntax_error(NOT_CMD, info));
	else
	{
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
	}
	return (true);
}

bool	check_double_input_error(int separator_count, int type, \
			t_minishell_info *info)
{
	if (separator_count == 1 || separator_count == 2)
		return (syntax_error(NOT_CMD, info));
	else if (separator_count == 3)
		return (syntax_error(OUTPUT, info));
	else
	{
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
	}
	return (true);
}

bool	check_single_input_error(int separator_count, int type, \
			t_minishell_info *info)
{
	if (separator_count == 1 || separator_count == 2)
		return (syntax_error(INPUT, info));
	else if (separator_count == 3)
		return (syntax_error(OUTPUT, info));
	else
	{
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
	}
	return (true);
}

bool	check_nothing_back_error(int separator_count, int type, \
			t_minishell_info *info)
{
	if (separator_count == 1 || separator_count == 2)
		return (syntax_error(NEWLINE, info));
	else if (separator_count == 3)
		return (syntax_error(OUTPUT, info));
	else
	{
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
	}
	return (true);
}

bool	check_separator_count_error(int separator_count, int type, \
			t_minishell_info *info)
{
	(void)type;
	if (separator_count == 3)
		return (syntax_error(OUTPUT, info));
	return (syntax_error(DB_OUTPUT, info));
}

bool	check_same_separator_error(int separator_count, int separator, \
			char *cmd, t_minishell_info *info)
{
	if (separator_count == 1 || separator_count == 2)
	{
		separator_count = 0;
		while (*cmd && *cmd == separator)
		{
			separator_count++;
			cmd++;
		}
	}
	if (separator_count == 1)
		return (syntax_error(OUTPUT, info));
	return (syntax_error(DB_OUTPUT, info));
}

static bool	check_next_chrs(char *cmd, t_minishell_info *info, char separator)
{
	int		separator_count;
	bool	space_flag;

	separator_count = 0;
	space_flag = false;
	while (*cmd && *cmd == separator)
	{
		separator_count++;
		cmd++;
	}
	printf("separator_count = %d\n", separator_count);
	if (*cmd == ' ')
		space_flag = true;
	(void)space_flag;
	cmd = skip_space(cmd);
	if (separator == '>')
	{
		// if (space_flag == true)
		// {
		// 	// if (*cmd == '\0')
		// 	// {
		// 	// 	if (separator_count == 1 || separator_count == 2)
		// 	// 		return (syntax_error(ERR_SYNTAX, "token `newline\'", info));
		// 	// 	if (separator_count == 3)
		// 	// 		return (syntax_error(ERR_SYNTAX, "token `>\'", info));
		// 	// 	else
		// 	// 		return (syntax_error(ERR_SYNTAX, "token `>>\'", info));

		// 	// }
		// 	// else if (*cmd == ';' || *cmd == '|' || *cmd == '>' || *cmd == '<')
		// 	// {

		// 	// }
		// 	;
		// }
		// else
		// {
			if (*cmd == ';' && *(cmd + 1) == ';')
				return (check_double_semicolon_error(separator_count, OUTPUT, info));
			else if (*cmd == ';')
				return (check_single_semicolon_error(separator_count, OUTPUT, info));
			else if (*cmd == '|' && *(cmd + 1) == '|')
				return (check_double_pipe_error(separator_count, OUTPUT, info));
			else if (*cmd == '|')
				return (check_single_pipe_error(separator_count, OUTPUT, info));
			else if (*cmd == '<' && *(cmd + 1) == '<')
				return (check_double_input_error(separator_count, OUTPUT, info));
			else if (*cmd == '<')
				return (check_single_input_error(separator_count, OUTPUT, info));
			else if (*cmd == '\0')
				return (check_nothing_back_error(separator_count, OUTPUT, info));
			else if (separator_count >= 3)
				return (check_separator_count_error(separator_count, OUTPUT, info));
			else if (*cmd == separator)
				return (check_same_separator_error(separator_count, separator, cmd, info));
			else
				return (true);
		// }
	}
	// printf("count = %d\n", separator_count);

	// if (*command || is_rc != NOT_FOUND)
	// {
	// 	if (is_rc != SEMICOLON && command[0] == '\0')
	// 		return (wait_next_cmd(info, 0));
	// 	else if (is_rc == PIPE && ispipe(*command))
	// 		warning_message(ERR_MANDATORY, info); // warningをどうするか
	// 	if (isdouble_output_redirect(*command, *(command + 1)))
	// 		return (syntax_error(ERR_SYNTAX, "token `>>\'", info));
	// 	else if (isoutput_redirect(*command, *(command + 1)) &&
	// 			ispipe(*(command + 1)))
	// 		return (syntax_error(ERR_SYNTAX, "token `>|\'", info));
	// 	else if (isoutput_redirect(*command, *(command + 1)))
	// 		return (syntax_error(ERR_SYNTAX, "token `>\'", info));
	// 	else if (is_rc == 3 && ispipe(*command))
	// 		return (syntax_error(ERR_SYNTAX, "token `|\'", info));
	// 	else if (is_rc == 2 && ispipe(*command))
	// 		return (syntax_error(ERR_SYNTAX, "token `newline\'", info));
	// 	else if (isdouble_semicolon(*command, *(command + 1)))
	// 		return (syntax_error(ERR_SYNTAX, "token `;;\'", info));
	// 	else if (issemicolon(*command, *(command + 1)))
	// 		return (syntax_error(ERR_SYNTAX, "token `;\'", info));
	// 	else if (*command == ' ' && skip_space(command)[0] == '\0')
	// 			return (syntax_error(ERR_SYNTAX, "token `newline\'", info));
	// 	else
	// 		return (true);
	// }
	// return (syntax_error(ERR_SYNTAX, "token `newline\'", info));
	return (false);
	(void)info;
}

static bool	check_pipe_or_redirect(char *command, t_minishell_info *info)
{
	// char			*tmp;
	// int				is_rc;
	bool			return_value;
	unsigned int	i;
	// char			separator;

	return_value = true;
	i = -1;
	while (command[++i])
	{
		if (command[i] == ';' || command[i] == '<' || command[i] == '>' || \
				command[i] == '|')
			if ((return_value = check_next_chrs(command + i, info, command[i])) \
					== false)
				return (false);
		// if (is_rc == SEMICOLON || is_rc == PIPE || is_rc == INPUT ||
		// 		is_rc == OUTPUT)
		// 	plus_index = 1;
		// else if (is_rc == DB_OUTPUT)
		// 	plus_index = 2;
		// tmp = command + i + plus_index;
		// if ((return_value = check_next_cmd(tmp, info, is_rc)) == false)
		// 	return (false);
		// command = info->command + i + plus_index;
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
	// rc = true;
	return (rc);
}
