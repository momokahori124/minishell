
<!-- output -->
bash-3.2$ pwd >>> pwd
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>> pwd
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>> pwd
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>>>>> pwd
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- newline -->
bash-3.2$ pwd >
bash: syntax error near unexpected token `newline'
bash-3.2$ pwd >>
bash: syntax error near unexpected token `newline'
bash-3.2$ pwd >>>
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>>
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- single_semicolon -->
bash-3.2$ pwd >; pwd
bash: syntax error near unexpected token `;'
bash-3.2$ pwd >>; pwd
bash: syntax error near unexpected token `;'
bash-3.2$ pwd >>>; pwd
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>>; pwd
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>>; pwd
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- double_semicolon -->
bash-3.2$ pwd >;; pwd
bash: syntax error near unexpected token `;;'
bash-3.2$ pwd >>;; pwd
bash: syntax error near unexpected token `;;'
bash-3.2$ pwd >>>;; pwd
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>>;; pwd
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>>;; pwd
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- single pipe -->
bash-3.2$ pwd >| a
pwdの内容がpwdファイルに入る

bash-3.2$ pwd > | a
bash: syntax error near unexpected token `|'

bash-3.2$ pwd >>| a
bash: syntax error near unexpected token `|'
bash-3.2$ pwd >>>| a
bash: syntax error near unexpected token `>|'
bash-3.2$ pwd >>>>| a
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>>| a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- double pipe -->
bash-3.2$ pwd >|| a
bash: syntax error near unexpected token `|'

bash-3.2$ pwd > || a
bash: syntax error near unexpected token `||'

bash-3.2$ pwd >>|| a
bash: syntax error near unexpected token `||'
bash-3.2$ pwd >> || a
bash: syntax error near unexpected token `||'
bash-3.2$ pwd >>>|| a
bash: syntax error near unexpected token `>|'
bash-3.2$ pwd >>>>|| a
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>>|| a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- single_input -->
bash-3.2$ pwd >< a
bash: syntax error near unexpected token `<'
bash-3.2$ pwd >>< a
bash: syntax error near unexpected token `<'
bash-3.2$ pwd >>>< a
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>>< a
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>>< a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- double_input -->
bash-3.2$ pwd ><< a
bash: syntax error near unexpected token `<<'
bash-3.2$ pwd >><< a
bash: syntax error near unexpected token `<<'
bash-3.2$ pwd >>><< a
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>><< a
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>><< a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space output-->
bash-3.2$ pwd > > a
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >> > a
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>> > a
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>> > a
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>> > a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space DB_output-->
bash-3.2$ pwd > >> a
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >> >> a
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>> >> a
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>> >> a
bash: syntax error near unexpected token `>>'
bash-3.2$ pwd >>>>> >> a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space pipe-->
bash-3.2$ pwd > |  a a
bash: syntax error near unexpected token `|'
bash-3.2$ pwd >> |  a
bash: syntax error near unexpected token `|'
bash-3.2$ pwd >>> |  a
bash: syntax error near unexpected token `>'
bash-3.2$ pwd >>>> | a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space DB_pipe-->

<!------------------>