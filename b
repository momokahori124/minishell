/Users/jinichiro/Desktop/tmp/minishell


bash-3.2$ ^[[A^[[A
bash: :s^[[A^[[A: substitution failed

bash-3.2$ pwd || aaa
/Users/jinichiro/Desktop/tmp/minishell
bash-3.2$ pwd | aaa
bash: aaa: command not found

bash-3.2$ return (true);
bash: syntax error near unexpected token `true'
bash-3.2$ return (tru);
bash: syntax error near unexpected token `tru'
bash-3.2$ return (tr);
bash: syntax error near unexpected token `tr'
bash-3.2$ return (t);
bash: syntax error near unexpected token `t'
bash-3.2$ return ();
bash: syntax error near unexpected token `;'
bash-3.2$ return ()
> bash: syntax error: unexpected end of file
bash-3.2$ which return
bash-3.2$ true
bash-3.2$ which true
/usr/bin/true
bash-3.2$ return ()
> c
bash: syntax error near unexpected token `c'
bash-3.2$ ()
bash: syntax error near unexpected token `)'
bash-3.2$ (
> )
bash: syntax error near unexpected token `)'

bash-3.2$ echo "a" < ppp
bash: ppp: No such file or directory
bash-3.2$ echo "a" ;< ppp
a
bash: ppp: No such file or directory

bash-3.2$ echo"a"
bash: echoa: command not found

bash-3.2$ echo "a |
> "
a |

bash-3.2$