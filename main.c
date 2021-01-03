/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:39:57 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/03 19:57:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>


#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(){
  errno = 0;
  execl("/bin/echo", "/bin/echo", "hoge", "fuga", NULL);

  if(errno != 0)
    perror(strerror(errno));

  return -1;
}

// int main(){
//   errno = 0;
//   char *a[] = {"/bin/ls", "hoge", "fuga", NULL};
//   execve("/bin/ls", a, NULL);

//   if(errno != 0)
//     perror(strerror(errno));

//   return -1;
// }
