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