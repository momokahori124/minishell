/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_etc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:44:40 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/13 23:45:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ETC_H
# define STRUCT_ETC_H

typedef struct		s_minishell_info
{
	char			*command;
	char			*current_dir_path;
	struct s_cmdlst	*cmd_lst;
}					t_minishell_info;

typedef struct		s_cmdlst
{
	char			*command;
	int				type;
	int				pipe[2];
	char			*arg;
	struct s_cmdlst	*next;
}					t_cmdlst;

enum	e_type
{
	PWD,
	TYPE_NUM,
};

#endif
