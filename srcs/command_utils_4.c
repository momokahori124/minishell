/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 00:07:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/24 17:03:00 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

static size_t	word_count(char const *s, char c)
{
	size_t		cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
	}
	return (cnt);
}

static size_t	word_length(char *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static int		switch_env_value(char **s, char **res, t_envlst *env_lst)
{
	int			exit_status;

	exit_status = g_signal.exit_status;
	if (**s == '$' && *(*(s) + 1) == '?')
	{
		(*s) += 2;
		if (!(*res = numjoin_str(*s, exit_status)))
			return (-2);
		return (-1);
	}
	if (**s == '$' && *(*(s) + 1) != '\0')
		*s = search_env((*s) + 1, ft_strlen((*s) + 1), env_lst);
	return (1);
}

static char		**insert_word(char *s, char c, size_t wc, t_envlst *env_lst)
{
	size_t		i;
	size_t		len;
	int			rc;
	char		**res;

	if (!(res = malloc(sizeof(char *) * (wc + 1))))
		return (NULL);
	i = -1;
	while (++i < wc)
	{
		while (*s == c)
			s++;
		if ((rc = switch_env_value(&s, &(res[i]), env_lst)) == -2)
			return (ptr_2d_free((void ***)&res, i));
		else if (rc == -1)
			continue ;
		len = word_length(s, c);
		if (!(res[i] = ft_substr(s, 0, len)))
			return (ptr_2d_free((void ***)&res, i));
		s += len;
	}
	res[i] = NULL;
	return (res);
}

char			**split_switch_env_value(char *s, char c, t_envlst *env_lst)
{
	char		**res;
	size_t		wc;

	if (!s)
		return (NULL);
	wc = word_count(s, c);
	if (wc == 0)
	{
		if (!(res = malloc(sizeof(char *) * 1)))
			return (NULL);
		res[0] = NULL;
		return (res);
	}
	res = insert_word(s, c, wc, env_lst);
	return (res);
}