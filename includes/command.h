/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:54 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 19:46:30 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "struct_etc.h"
# include "minishell.h"
# include "exit.h"
# include "pipe_redirect.h"


// pid_t		g_bin_fork_pid;

typedef struct	s_global
{
	pid_t	fork_pid;
	int		exit_status;
}				t_global;
t_global	g_signal;

// typedef struct	s_sig
// {
// 	int				sigint;
// 	int				sigquit;
// 	int				exit_status;
// 	pid_t			pid;
// }				t_sig;

// t_sig	g_sig;

// char	*read_command_line(t_minishell_info *info);
char	*waiting_for_input(t_minishell_info *info);
// bool	read_command_line(t_minishell_info *info);
bool	parse_command(t_minishell_info *info, char *command);
bool	is_command_exit(char *cmd);

void	add_back_command_lst(t_minishell_info *info, char **command, int type);
void	exec_pwd(t_minishell_info *info);

char	*next_command(char *command);
// void	cmd_lstadd_back(t_cmdlst **begin, t_cmdlst *new);
// t_cmdlst	*skip_lst_and_free(t_cmdlst **cmd_lst, int how_many);

void	rm_chr_in_str(char **str, char chr);
ssize_t	safe_read(char *buf, char **ptr, t_minishell_info *info);

bool	rm_quotation(t_minishell_info *info);
// bool	wait_quotation(char first_appear, char **command, t_minishell_info *info);
char	*waiting_for_quotation(char first_quo, char **command,
					t_minishell_info *info);

// char		**wait_for_next_cmd(char ***cmd_grp, int array_size, t_minishell_info *info);
// bool	wait_for_next_cmd(char ***cmd_grp, int array_size, t_minishell_info *info);
int		waiting_for_next_command(char ***cmd_grp, int array_size,
								t_minishell_info *info);
int		add_command_group(char **split, t_cmd_grp *cmd_grp_info, int split_size,
					t_minishell_info *info);


void	execute_each_command_loop(t_minishell_info *info);
// bool	execute_each_command(t_minishell_info *info, int type, char *cmd);
bool	execute_each_command(t_minishell_info *info, t_cmdlst *cmd);
void	free_alloc_ptr_in_cmd_lst(t_cmdlst **cmd_lst);

// t_cmdlst	*redirect_sep(t_minishell_info *info, t_cmdlst **cmd_lst);

// utils2
// char	**split_by_chrs_contain_delimiters(char *str, char *charset);
char	**split_each_parts(char *str);
bool		isalnum_except_next_redir(char *str);

// utils3
char	**rm_spaces_in_2d_array(char **arr, t_minishell_info *info);

// utils4
char			**split_and_switch_env_value(char *s, char c, t_envlst *env_lst);
int		switch_env_value(char **s, char **res, t_envlst *env_lst);

// format
bool	check_format_of_command(char ***grp, t_minishell_info *info);

//is_out
bool	is_output_format_error(char ***grp, int i, t_minishell_info *info);

//is_pipe
bool	is_pipe_format_error(char ***grp, int i, t_minishell_info *info);

//is_semi
bool		is_semicolon_format_error(char ***grp, int i, \
				t_minishell_info *info);

void	exec_cd(t_minishell_info *info, t_cmdlst *cmd);
bool	is_symbolic_dir(t_minishell_info *info, char *dir_name);
void	trace_symbolic_src(t_minishell_info *info, char *dir_name);

void		exec_bin(t_minishell_info *info, char **args);
// bool	check_bash_standard_commands(t_minishell_info *info, char ***command);

void	update_env_lst(t_envlst **env_lst, char *env_name, char *env_value,
							t_minishell_info *info);

void	exec_env(t_minishell_info *info, char *arg);

void	exec_export(t_minishell_info *info, char **args);

void	exec_unset(t_minishell_info *info, char **args);
void	exec_echo(t_minishell_info *info, t_cmdlst *cmd);

#endif
