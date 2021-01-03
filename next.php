<!-- bash-3.2$ pwd >>> pwd
bash: syntax error near unexpected token `>'

bash-3.2$ pwd >>>> pwd
bash: syntax error near unexpected token `>>'

bash-3.2$ pwd >>>>>>>> pwd
bash: syntax error near unexpected token `>>' -->

bash-3.2$ pwd >; pwd
bash: syntax error near unexpected token `;'
bash-3.2$ pwd >>; pwd
bash: syntax error near unexpected token `;'

bash-3.2$ pwd >;; pwd
bash: syntax error near unexpected token `;;'
bash-3.2$ pwd >>;; pwd
bash: syntax error near unexpected token `;;'

bash-3.2$ pwd >>>;; pwd
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>; pwd
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>>; pwd
bash: syntax error near unexpected token `>>'

bash-3.2$ pwd >>| pwd
bash: syntax error near unexpected token `|'
bash-3.2$ pwd >>|| pwd
bash: syntax error near unexpected token `||'

bash-3.2$ pwd >>>| a
bash: syntax error near unexpected token `>|'
bash-3.2$ pwd >>>|| a
bash: syntax error near unexpected token `>|'

bash-3.2$ pwd >| pwd
pwdの内容がpwdファイルに入る
bash-3.2$ pwd >|| pwd
bash: syntax error near unexpected token `|'
bash-3.2$ pwd >||| pwd
bash: syntax error near unexpected token `||'

<!-- bash-3.2$ pwd >>>
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>>
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>
bash: syntax error near unexpected token `newline'
bash-3.2$ pwd >
bash: syntax error near unexpected token `newline' -->

<!-- ======================================================== -->


bash-3.2$ pwd ||| pwd
bash: syntax error near unexpected token `|'

bash-3.2$ pwd |||| pwd
bash: syntax error near unexpected token `||'

bash-3.2$ pwd ||||| pwd
bash: syntax error near unexpected token `||'

bash-3.2$ pwd ;; pwd
bash: syntax error near unexpected token `;;'

bash-3.2$ pwd ;;;;; pwd
bash: syntax error near unexpected token `;;'

bash-3.2$ pwd ;> pwd
/Users/jinichiro/Desktop/tmp/minishell
bash-3.2$ pwd ;>> pwd
/Users/jinichiro/Desktop/tmp/minishell


bash-3.2$ pwd <<< pwd
/Users/jinichiro/Desktop/tmp/minishell
bash-3.2$ pwd <<<< pwd
bash: syntax error near unexpected token `<'

bash-3.2$ pwd ||>
bash: syntax error near unexpected token `newline'
bash-3.2$ pwd |>
bash: syntax error near unexpected token `newline'
bash-3.2$ pwd |>>
bash: syntax error near unexpected token `newline'
bash-3.2$ pwd |>>>
bash: syntax error near unexpected token `>'

bash-3.2$ pwd ;;;| a
bash: syntax error near unexpected token `;;'
bash-3.2$ pwd <<<| a
bash: syntax error near unexpected token `|'
bash-3.2$ pwd <<<|| a
bash: syntax error near unexpected token `||'