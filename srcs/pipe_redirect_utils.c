/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/18 03:00:47 by tjinichi         ###   ########.fr       */
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

/*
** "pwd|"の後に"|"を打つとエラーで"aaa|"を打つと続行なのでこんな再帰を使ってる
** もしかしたらもっとわかりやすいやり方あるかも
*/

// bool	error_or_recursive(char buf, char **inputs, t_minishell_info *info)
// {
// 	bool	res;

// 	res = true;
// 	if (buf == '|')
// 		res = syntax_error(PIPE, info);
// 	else if (buf == '>')
// 	return (true);
// }

bool	check_next_chrs(char *cmd, t_minishell_info *info, char separator);
bool	check_pipe_or_redirect(char *command, t_minishell_info *info);


bool		wait_next_cmd(t_minishell_info *info, int cnt)
{
	ssize_t		rc;
	char		buf;
	char		*inputs;
	// int			count = 0;

	(void)cnt;
	// bool aaaa = false;
	write(1, "> ", 2);
	if (!(inputs = ft_strdup("")))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	while ((rc = safe_read(&buf, &inputs, info)) >= 0)
	{
		printf("[%c]\n", buf);
		if (write(0, "\033[0K", 4) < 0)
		{
			ptr_free((void **)&inputs);
			all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		}
		if (rc != 0)
		{
			if (buf != ' ' && buf != '\n')
			{
				inputs = re_strjoinch(&inputs, buf);
			}
		}
		if (rc == 0 && buf == '\0')
			return (syntax_error(SYNTAX_EOL_NUM, info));
		if (buf == '\n')
		{
			if (check_pipe_or_redirect(inputs, info) == false)
				return (false);
			info->command = re_strjoin(&(info->command), inputs);
			inputs = re_strdup(&inputs, "");
			write(1, "> ", 2);
			break ;
		}
	}
	// info->command = re_strjoin(&(info->command), inputs);
	printf("commnad = [%s]\n", info->command);
	if (check_pipe_or_redirect(inputs, info) == false)
		return (false);
	ptr_free((void **)&inputs);
	if (rc == -1)
		all_free_perror_exit(info, ERR_READ, __LINE__, __FILE__);
	return (true);
}

bool	check_pipe_num(int count, t_minishell_info *info)
{
	if (count == 1)
		return (wait_next_cmd(info, 0));
	return (false);
}

bool	check_next_chrs(char *cmd, t_minishell_info *info, char separator)
{
	int		separator_count;
	bool	space_flag;

	separator_count = char_num_in_str(cmd, separator);
	space_flag = false;
	printf("separator_count = %d\n", separator_count);
	printf("chr = %c\n", separator);
	printf("cmd = %s\n", cmd);
	if (cmd[separator_count] == ' ')
		space_flag = true;
	cmd = skip_space(cmd + separator_count);
	if (separator == '>')
		return (inspect_output_pattern(cmd, separator_count, space_flag, info));
	else if (separator == ';')
		return (inspect_semicolon_pattern(cmd, separator_count, space_flag, info));
	else if (separator == '|')
	{
		if (separator_count == 2)
			return (syntax_error(NOT_CMD, info));
		else if (separator_count == 3)
			return (syntax_error(PIPE, info));
		else if (separator_count == 4)
			return (syntax_error(NOT_CMD, info));
		else if (*cmd == '\0')
			return (check_pipe_num(separator_count, info));
		else if (*cmd == '|')
			return (syntax_error(PIPE, info));
		else
			return (true);
	}
	return (true);
	return (false);
}

bool	check_pipe_or_redirect(char *command, t_minishell_info *info)
{
	bool			return_value;
	unsigned int	i;

	return_value = true;
	i = -1;
	while (command[++i])
	{
		if (command[i] == ';' || command[i] == '<' || command[i] == '>' || \
				command[i] == '|')
			if ((return_value = check_next_chrs(command + i, info, command[i]))
					== false)
			{
				ptr_free((void **)&command);
				return (false);
			}
	}
	return (return_value);
}



char	**insert_2d_array(char **dst, char **src1, char **src2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (src1[i])
	{
		dst[i] = src1[i];
		i++;
	}
	j = 0;
	while (src2[j])
	{
		dst[i + j] = src2[j];
		j++;
	}
	dst[i + j] = NULL;
	return (dst);
}


int		add_cmd_grp(char **split, t_cmd_grp *cmd_grp_info, int split_size, t_minishell_info *info)
{
	char	**res;
	char	***cmd_grp;
	int		array_size;

	cmd_grp = cmd_grp_info->cmd_grp;
	array_size = cmd_grp_info->array_size;
	if (!(res = malloc(sizeof(char *) * (split_size + array_size + 1))))
	{
		ptr_2d_free((void ***)cmd_grp, array_size);
		ptr_2d_free((void ***)&split, split_size);
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	res = insert_2d_array(res, *cmd_grp, split);
	cmd_grp_info->array_size += split_size;
	ptr_2d_free((void ***)cmd_grp, 0);
	ptr_2d_free((void ***)&split, 0);
	*(cmd_grp_info->cmd_grp) = res;
	return (NEXT_CMD);
}

int		check_more_pipe(char **inputs, t_cmd_grp *cmd_grp_info, t_minishell_info *info)
{
	char	**split;
	int		i;

	if ((*inputs)[0] == '\0')
		return (true);
	if (!(split = split_by_chrs_contain_delimiters(*inputs, "|;><")))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	ptr_free((void **)inputs);
	i = 0;
	while (split[i])
	{
		// pipeの読み込み中にいろいろエラーを弾く。
		if (i != 0 && split[i][0] == '|' && split[i][1] != '|' && !split[i + 1])
			return (add_cmd_grp(split, cmd_grp_info, i + 1, info));
		else if (split[i][0] == '|' && split[i][1] == '|')
			return (two_ptr_2d_free_and_syntax_error(DB_PIPE, &split, cmd_grp_info, info));
		i++;
	}
	add_cmd_grp(split, cmd_grp_info, i, info);
	return (true);
}

static char	*prepare_in_advance(t_minishell_info *info, \
			t_cmd_grp *cmd_grp_info, char ***cmd_grp, int array_size)
{
	char	*res;

	cmd_grp_info->cmd_grp = cmd_grp;
	cmd_grp_info->array_size = array_size;
	if (write(1, "> ", 2) < 0)
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!(res = ft_strdup("")))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	return (res);
}

static bool	check_buf_and_return_value(ssize_t rc, char **inputs, char buf, \
			t_minishell_info *info)
{
	if (rc != 0)
	{
		if (buf != ' ' && buf != '\n')
			*inputs = re_strjoinch(inputs, buf);
	}
	else if (rc == 0 && ((*inputs) == NULL || (*inputs)[0] == '\0'))
	{
		ptr_free((void **)inputs);
		syntax_error(SYNTAX_EOL_NUM, info);
		return (false);
	}
	return (true);
}

static bool	do_when_input_char_equal_newline(char **inputs, t_cmd_grp *cmd_grp_info, t_minishell_info *info)
{
	int	rc;

	rc = check_more_pipe(inputs, cmd_grp_info, info);
	printf("rc : %d\n", rc);
	if (rc != NEXT_CMD)
	{
		if (rc == false)
			*(cmd_grp_info->cmd_grp) = NULL;
		return (false);
	}
	write(1, "> ", 2);
	return (NEXT_CMD);
}

bool	wait_for_next_cmd(char ***cmd_grp, int array_size, t_minishell_info *info)
{
	ssize_t		rc;
	char		buf;
	char		*inputs;
	t_cmd_grp cmd_grp_info;

	inputs = prepare_in_advance(info, &cmd_grp_info, cmd_grp, array_size);
	while ((rc = safe_read(&buf, &inputs, info)) >= 0)
	{
		if (write(0, "\033[0K", 4) < 0)
		{
			ptr_free((void **)&inputs);
			all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		}
		if (check_buf_and_return_value(rc, &inputs, buf, info) == false)
		{
			ptr_2d_free((void ***)cmd_grp_info.cmd_grp, cmd_grp_info.array_size);
			return (false);
		}
		if (buf == '\n')
			if (do_when_input_char_equal_newline(&inputs, &cmd_grp_info, info) == false)
				return (true);
	}
	return (false);
}
