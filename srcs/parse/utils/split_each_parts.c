/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_each_parts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:54:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 04:03:15 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/command.h"

static bool		isalnum_except_next_redir(char *str)
{
	// printf("%c\n", *str);
	return (!((*str == '|' || *str == '>' || *str == '<' || *str == ';')
			&& *(str + 1) != '>'));
}

static size_t	count_words(char *str)
{
	size_t		word_count;
	int			flag;

	word_count = 0;
	flag = 0;
	while (*str)
	{
		while (*str && (isalnum_except_next_redir(str) || *str == ' ') && (flag = 1))
			str++;
		if (*str && !(isalnum_except_next_redir(str) || *str == ' '))
		{
			if (flag == 1)
				word_count += 2;
			else
				word_count++;
			flag = 0;
			while (*str && !(isalnum_except_next_redir(str) || *str == ' '))
				str++;
		}
	}
	return (word_count + flag);
}

static char		*insert_word(char **str)
{
	char		*word;
	size_t		i;

	i = 0;
	while ((*str)[i] && !(isalnum_except_next_redir(&(*str)[i]) || (*str)[i] == ' '))
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (**str && !(isalnum_except_next_redir(*str) || **str == ' '))
	{
		word[i] = **str;
		i++;
		(*str)++;
	}
	word[i] = '\0';
	return (word);
}

static char		*insert_separator(char **str)
{
	char		*word;
	size_t		i;

	i = 0;
	while ((*str)[i] && (isalnum_except_next_redir(&(*str)[i]) || (*str)[i] == ' '))
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (**str && (isalnum_except_next_redir(*str) || **str == ' '))
	{
		word[i] = **str;
		i++;
		(*str)++;
	}
	word[i] = '\0';
	return (word);
}

char			**split_each_parts(char *str)
{
	char		**res;
	size_t		word_count;
	size_t		i;

	word_count = count_words(str);
	if (!(res = malloc(sizeof(char *) * (word_count + 1))))
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		if (*str && (isalnum_except_next_redir(str) || *str == ' '))
			if (!(res[i++] = insert_separator(&str)))
				return (ptr_2d_free((void***)&res, --i));
		if (*str && !(isalnum_except_next_redir(str) || *str == ' '))
			if (!(res[i++] = insert_word(&str)))
				return (ptr_2d_free((void***)&res, --i));
	}
	res[i] = NULL;
	return (res);
}
