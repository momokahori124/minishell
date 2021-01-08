<!-- normal -->
echo "a" | pwd
/Users/jinichiro/Desktop/tmp/minishell
<!-- ------- -->

<!-- error -->
echo "a" || pwd
a
echo "a" ||| pwd
bash: syntax error near unexpected token `|'
echo "a" |||| pwd
bash: syntax error near unexpected token `||'
<!-- ------- -->

<!-- newline -->
echo "a" |
> bash: syntax error: unexpected end of file
echo "a" |
> pwd
/Users/jinichiro/Desktop/tmp/minishell
echo "a" ||
> bash: syntax error: unexpected end of file
echo "a" |||
bash: syntax error near unexpected token `|'
echo "a" ||||
bash: syntax error near unexpected token `||'
<!-- ------- -->

<!-- output -->
echo "a" |> pwd
echo "a" |>> pwd
echo "a" |>>> pwd
bash: syntax error near unexpected token `>'
echo "a" |>>>> pwd
bash: syntax error near unexpected token `>>'
<!-- ------- -->

<!-- semicolon -->
echo "a" |; pwd
bash: syntax error near unexpected token `;'
echo "a" |;; pwd
bash: syntax error near unexpected token `;;'
echo "a" |;;; pwd
bash: syntax error near unexpected token `;;'
<!-- ------- -->

<!-- input -->
echo "a" |< pwd
echo "a" |< pwd
bash: pwd: No such file or directory
> echo "a" |<< pwd
> s
>
echo "a" |<<< pwd 対応しない
echo "a" |<<<< pwd
bash: syntax error near unexpected token `<'
echo "a" |<<<<< pwd
bash: syntax error near unexpected token `<<'
<!-- ------- -->