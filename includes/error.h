/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:51:32 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/14 00:24:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"
# define ERR_READ "Failed to read at the above location. "
# define ERR_MALLOC "Failed to malloc at the above location. "

void		perror_exit(char *error_message, int state);
void		free_perror_exit(char *ptr, char *error_message, int state);
void		free_exit(char *ptr, int state);
void		all_free_perror_exit(t_minishell_info *info, char *error_message, \
					int state);

void		ctrl_d_exit(char *ptr);

#endif
