<!-- normal -->
bash-3.2$ echo "a" | pwd
/Users/jinichiro/Desktop/tmp/minishell
<!-- ------- -->

<!-- error -->
bash-3.2$ echo "a" || pwd
a
bash-3.2$ echo "a" ||| pwd
bash: syntax error near unexpected token `|'
bash-3.2$ echo "a" |||| pwd
bash: syntax error near unexpected token `||'
<!-- ------- -->

<!-- newline -->
bash-3.2$ echo "a" |
> bash: syntax error: unexpected end of file
bash-3.2$ echo "a" |
> pwd
/Users/jinichiro/Desktop/tmp/minishell
bash-3.2$ echo "a" ||
> bash: syntax error: unexpected end of file
bash-3.2$ echo "a" |||
bash: syntax error near unexpected token `|'
bash-3.2$ echo "a" ||||
bash: syntax error near unexpected token `||'
<!-- ------- -->

<!-- output -->
bash-3.2$ echo "a" |> pwd
bash-3.2$ echo "a" |>> pwd
bash-3.2$ echo "a" |>>> pwd
bash: syntax error near unexpected token `>'
bash-3.2$ echo "a" |>>>> pwd
bash: syntax error near unexpected token `>>'
<!-- ------- -->

<!-- semicolon -->
bash-3.2$ echo "a" |; pwd
bash: syntax error near unexpected token `;'
bash-3.2$ echo "a" |;; pwd
bash: syntax error near unexpected token `;;'
bash-3.2$ echo "a" |;;; pwd
bash: syntax error near unexpected token `;;'
<!-- ------- -->