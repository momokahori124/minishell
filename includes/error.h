/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:51:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/18 02:15:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"
# include "struct_etc.h"
# define ERR_READ "Failed to \033[4mread\033[0m at the above location. "
# define ERR_WRITE "Failed to \033[4mwrite\033[0m at the above location. "
# define ERR_MALLOC "Failed to \033[4mmalloc\033[0m at the above location. "
# define ERR_EXECVE "Failed to \033[4mexecve\033[0m at the above location. "
# define ERR_FORK "Failed to \033[4mfork\033[0m at the above location. "
# define ERR_FAIL_CHILD "The child process did not terminate successfully. "
# define ERR_WAIT_PID "Failed to \033[4mwait_pid\033[0m at the above location. "
# define ERR_PIPE "Failed to \033[4mpipe\033[0m at the above location. "
# define ERR_OPEN "Failed to \033[4mopen\033[0m at the above location. "
# define ERR_CLOSE "Failed to \033[4mclose\033[0m at the above location. "
# define ERR_DUP "Failed to \033[4mdup\033[0m at the above location. "
# define ERR_DUP2 "Failed to \033[4mdup2\033[0m at the above location. "


# define SYNTAX_EOL_NUM -1
# define SYNTAX_EOL "minishell: syntax error: unexpected end of file\n"

# define WARNING -2
# define NEWLINE -3


# define SYNTAX "minishell: syntax error near unexpected "
# define SYNTAX_OP "minishell: syntax error near unexpected token `>\'\n"
# define SYNTAX_DB_OP "minishell: syntax error near unexpected token `>>\'\n"
# define SYNTAX_SEMICOLON "minishell: syntax error near unexpected token `;\'\n"
# define SYNTAX_PIPE "minishell: syntax error near unexpected token `|\'\n"
# define SYNTAX_INPUT "minishell: syntax error near unexpected token `<\'\n"
# define SYNTAX_NL "minishell: syntax error near unexpected token `newline\'\n"

# define ERR_MANDATORY "That command is not supported by mandatory.\n"
# define ERR_DB_SEMICOLON "minishell: `;;\' is not supported by mandatory.\n"
# define ERR_DB_PIPE "minishell: `||\' is not supported by mandatory.\n"
# define ERR_OUTPUT_PIPE "minishell: `>|\' is not supported by mandatory.\n"
# define ERR_DB_INPUT "minishell: `<<\' is not supported by mandatory.\n"
# define ERR_TR_INPUT "minishell: `<<<\' is not supported by mandatory.\n"


void	perror_exit(char *error_message, int line_num, char *file_name);
void	free_perror_exit(char *ptr, char *error_message, int line_num, \
				char *file_name);
void	free_exit(char **ptr, int state);
void	all_free_perror_exit(t_minishell_info *info, char *error_message, \
				int line_num, char *file_name);

void	ctrl_d_exit(char **ptr, t_minishell_info *info);
bool	syntax_error(int type, t_minishell_info *info);
bool	two_ptr_2d_free_and_syntax_error(int type, char ***array, t_cmd_grp *cmd_grp_info, t_minishell_info *info);
bool	ptr_2d_free_and_syntax_error(int type, char ***cmd_grp, t_minishell_info *info);
bool	syntax_warning(int type);
bool	warning_message(char *error_message, t_minishell_info *info);

void		all_free_minishell_info(t_minishell_info *info);
void	err_no_such_file_or_directory(char *filename, t_minishell_info *info);

#endif
