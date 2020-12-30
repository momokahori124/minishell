/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_etc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:44:40 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/30 21:54:05 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ETC_H
# define STRUCT_ETC_H

typedef struct		s_minishell_info
{
	char			*command;
	char			*current_dir_path;
	int				prev_rc;
	char			**cmd_split;
	struct s_cmdlst	*cmd_lst;
}					t_minishell_info;

typedef struct		s_cmdlst
{
	int				type;
	int				pipe[2];
	char			**arg;
	struct s_cmdlst	*next;
}					t_cmdlst;

enum	e_cmd
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
	CMD_NUM,
};
# define NOT_CMD CMD_NUM

#endif
