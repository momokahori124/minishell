/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/05 20:02:44 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe_redirect.h"

size_t		char_num_in_str(char *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

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
	printf("cnt : {%d}\n", separator_count);
	printf("type : {%d}\n", type);
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
			bool flag, t_minishell_info *info)
{
	printf("cnt : {%d}\n", separator_count);
	printf("type : {%d}\n", type);
	printf("flag : {%d}\n", flag);
	if (separator_count == 1)
		if (flag == false)
			return (syntax_error(PIPE, info));
		else
			return (syntax_error(NOT_CMD, info));
	// else if (separator_count == 2)
	// 	return (syntax_error(NOT_CMD, info));
	else if (separator_count == 2 || separator_count == 3)
		if (separator_count == 2 || flag == false)
			return (syntax_error(NOT_CMD, info));
		else
			return (syntax_error(OUTPUT, info));
	else
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
	return (true);
}

bool	check_single_pipe_error(int separator_count, int type, \
			bool flag, t_minishell_info *info)
{
	if (separator_count == 1)
		if (flag == false)
			// return (true);
			return (syntax_warning(WARNING));
		else
			return (syntax_error(PIPE, info));
	else if (separator_count == 2)
		return (syntax_error(PIPE, info));
	else if (separator_count == 3)
		if (flag == false)
			return (syntax_error(NOT_CMD, info));
		else
			return (syntax_error(OUTPUT, info));
	else
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
	return (true);
}

bool	check_double_input_error(int separator_count, int type, \
			t_minishell_info *info)
{
	if (separator_count == 0)
		return (true);
	else if (separator_count == 1 || separator_count == 2)
		return (syntax_error(NOT_CMD, info));
	else if (separator_count == 3)
		return (syntax_error(type, info));
	else
	{
		if (type == OUTPUT)
			return (syntax_error(DB_OUTPUT, info));
		if (type == INPUT)
			return (syntax_error(NOT_CMD, info));
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

bool	inspect_output_pattern(char *cmd, int separator_count,
			bool flag, t_minishell_info *info)
{
	if (char_num_in_str(cmd, '|') >= 3)
		flag = true;
	if (*cmd == ';' && *(cmd + 1) == ';')
		return (check_double_semicolon_error(separator_count, OUTPUT, info));
	else if (*cmd == ';')
		return (check_single_semicolon_error(separator_count, OUTPUT, info));
	else if (*cmd == '|' && *(cmd + 1) == '|')
		return (check_double_pipe_error(separator_count, OUTPUT, flag, info));
	else if (*cmd == '|')
		return (check_single_pipe_error(separator_count, OUTPUT, flag, info));
	else if (*cmd == '<' && *(cmd + 1) == '<')
		return (check_double_input_error(separator_count, OUTPUT, info));
	else if (*cmd == '<')
		return (check_single_input_error(separator_count, OUTPUT, info));
	else if (*cmd == '\0')
		return (check_nothing_back_error(separator_count, OUTPUT, info));
	else if (separator_count >= 3)
		return (check_separator_count_error(separator_count, OUTPUT, info));
	else if (*cmd == '>')
		return (check_same_separator_error(separator_count, '>', cmd, info));
	else
		return (true);
}

bool	inspect_semicolon_pattern(char *cmd, int separator_count,
			bool flag, t_minishell_info *info)
{
	if (separator_count >= 2)
		return (syntax_error(NOT_CMD, info));
	else if (*cmd == '\0')
		return (true);
	else if (*cmd == '>' && (separator_count = char_num_in_str(cmd, '>')))
		return (inspect_output_pattern(skip_space(cmd + separator_count), separator_count, flag, info));
	else if (*cmd == '|' && (separator_count = char_num_in_str(cmd, '|')))
		return (check_double_pipe_error(1, OUTPUT, separator_count - 1, info));
	else if (*cmd == '<' && (separator_count = char_num_in_str(cmd, '<')))
		return (check_double_input_error(separator_count - 1, INPUT, info));
	else if (*cmd == ';' && (separator_count = char_num_in_str(cmd, ';')))
		return (check_single_semicolon_error(separator_count + 1, NOT_CMD, info));
	else
		return (true);
}

static bool	check_next_chrs(char *cmd, t_minishell_info *info, char separator)
{
	int		separator_count;
	bool	space_flag;

	separator_count = char_num_in_str(cmd, separator);
	space_flag = false;
	// while (cmd[separator_count] && cmd[separator_count] == separator)
	// 	separator_count++;
	printf("separator_count = %d\n", separator_count);
	printf("chr = %c\n", separator);
	if (cmd[separator_count] == ' ')
		space_flag = true;
	cmd = skip_space(cmd + separator_count);
	if (separator == '>')
		return (inspect_output_pattern(cmd, separator_count, space_flag, info));
	else if (separator == ';')
		return (inspect_semicolon_pattern(cmd, separator_count, space_flag, info));
	else if (separator == '|')
	{

	}
	return (true);
	return (false);
}

static bool	check_pipe_or_redirect(char *command, t_minishell_info *info)
{
	bool			return_value;
	unsigned int	i;

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
