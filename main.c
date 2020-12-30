/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:39:57 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/30 19:30:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>

void	str_tolower(char **s)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = *s;
	while (tmp[i])
	{
		tmp[i] = tolower(tmp[i]);
		i++;
	}
}

int main()
{
	char *s = strdup("ABccDFRd");

	str_tolower(&s);
	printf("%s\n", s);
	free(s);
}
