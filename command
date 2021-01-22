bash-3.2$ echo /$USER
/jinichiro
bash-3.2$ echo \$USER
$USER
bash-3.2$ echo \USER
USER


bash-3.2$ cat pppppppp
cat: pppppppp: No such file or directory
bash-3.2$ cat pppppppp 2       > a
cat: pppppppp: No such file or directory
cat: 2: No such file or directory
bash-3.2$ cat pppppppp a
cat: pppppppp: No such file or directory
bash-3.2$ cat pppppppp 2
cat: pppppppp: No such file or directory
cat: 2: No such file or directory

bash-3.2$ info
bash-3.2$ info->cmd_lst->next->type
bash: info-: command not found


bash-3.2$ cd tmp
bash-3.2$ pwd
/Users/jinichiro/Desktop/minishell4/tmp
bash-3.2$ cd -P tmp
bash-3.2$ pwd
/Users/jinichiro/Desktop/minishell4/includes
bash-3.2$ ls -l tmp
lrwxr-xr-x  1 jinichiro  staff  8  1 23 01:30 tmp -> includes