/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_etc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:44:40 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/14 02:39:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ETC_H
# define STRUCT_ETC_H

typedef struct stat t_stat;

typedef struct		s_minishell_info
{
	char			*command;
	char			*current_dir_path;
	int				prev_rc;
	char			**cmd_split;
	char			**envp;
	struct s_cmdlst	*cmd_lst;
}					t_minishell_info;

typedef struct		s_cmdlst
{
	int				type;
	int				pipe[2];
	char			**arg;
	struct s_cmdlst	*next;
}					t_cmdlst;

typedef struct		s_cmd_grp
{
	char			***cmd_grp;
	int				array_size;
}					t_cmd_grp;

enum	e_cmd
{
	BIN,
	SEMICOLON,
	INPUT,
	OUTPUT,
	DB_OUTPUT,
	OUTPUT_PIPE,
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
	PIPE,
	CMD_NUM,
};
# define NOT_CMD CMD_NUM
# define DB_SEMICOLON CMD_NUM + 1
# define DB_PIPE CMD_NUM + 2
# define OUTPUT_PIPE CMD_NUM + 3
# define DB_INPUT CMD_NUM + 4
# define TR_INPUT CMD_NUM + 5

// # define SEMICOLON SEMICOLON
// # define INPUT INPUT
// # define OUTPUT OUTPUT
// # define DB_OUTPUT DB_OUTPUT
// # define PIPE PIPE
# define NOT_FOUND -1
# define NOT_FOUND -1

# define NEXT_CMD 2

#endif
