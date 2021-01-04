
<!-- output -->
pwd >>> pwd
bash: syntax error near unexpected token `>'
pwd >>>> pwd
bash: syntax error near unexpected token `>>'
pwd >>>>> pwd
bash: syntax error near unexpected token `>>'
pwd >>>>>>>> pwd
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- newline -->
pwd >
bash: syntax error near unexpected token `newline'
pwd >>
bash: syntax error near unexpected token `newline'
pwd >>>
bash: syntax error near unexpected token `>'
pwd >>>>
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- single_semicolon -->
pwd >; pwd
bash: syntax error near unexpected token `;'
pwd >>; pwd
bash: syntax error near unexpected token `;'
pwd >>>; pwd
bash: syntax error near unexpected token `>'
pwd >>>>; pwd
bash: syntax error near unexpected token `>>'
pwd >>>>>; pwd
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- double_semicolon -->
pwd >;; pwd
bash: syntax error near unexpected token `;;'
pwd >>;; pwd
bash: syntax error near unexpected token `;;'
pwd >>>;; pwd
bash: syntax error near unexpected token `>'
pwd >>>>;; pwd
bash: syntax error near unexpected token `>>'
pwd >>>>>;; pwd
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- single pipe -->
pwd >| a
pwdの内容がpwdファイルに入る
pwd > | a
bash: syntax error near unexpected token `|'
pwd >>| a
bash: syntax error near unexpected token `|'
pwd >>>| a
bash: syntax error near unexpected token `>|'
pwd >>>>| a
bash: syntax error near unexpected token `>>'
pwd >>>>>| a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- double pipe -->
pwd >|| a
bash: syntax error near unexpected token `|'
pwd > || a
bash: syntax error near unexpected token `||'
pwd >>|| a
bash: syntax error near unexpected token `||'
pwd >> || a
bash: syntax error near unexpected token `||'
pwd >>>|| a
bash: syntax error near unexpected token `>|'
pwd >>>>|| a
bash: syntax error near unexpected token `>>'
pwd >>>>>|| a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- single_input -->
pwd >< a
bash: syntax error near unexpected token `<'
pwd >>< a
bash: syntax error near unexpected token `<'
pwd >>>< a
bash: syntax error near unexpected token `>'
pwd >>>>< a
bash: syntax error near unexpected token `>>'
pwd >>>>>< a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- double_input -->
pwd ><< a
bash: syntax error near unexpected token `<<'
pwd >><< a
bash: syntax error near unexpected token `<<'
pwd >>><< a
bash: syntax error near unexpected token `>'
pwd >>>><< a
bash: syntax error near unexpected token `>>'
pwd >>>>><< a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space output-->
pwd > > a
bash: syntax error near unexpected token `>'
pwd >> > a
bash: syntax error near unexpected token `>'
pwd >>> > a
bash: syntax error near unexpected token `>'
pwd >>>> > a
bash: syntax error near unexpected token `>>'
pwd >>>>> > a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space DB_output-->
pwd > >> a
bash: syntax error near unexpected token `>>'
pwd >> >> a
bash: syntax error near unexpected token `>>'
pwd >>> >> a
bash: syntax error near unexpected token `>'
pwd >>>> >> a
bash: syntax error near unexpected token `>>'
pwd >>>>> >> a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space pipe-->
pwd > |  a a
bash: syntax error near unexpected token `|'
pwd >> |  a
bash: syntax error near unexpected token `|'
pwd >>> |  a
bash: syntax error near unexpected token `>'
pwd >>>> | a
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space DB_pipe-->
pwd > || ls
bash: syntax error near unexpected token `||'
pwd >> || ls
bash: syntax error near unexpected token `||'
pwd >>> || ls
bash: syntax error near unexpected token `>'
pwd >>>> || ls
bash: syntax error near unexpected token `>>'
pwd >>>>> || ls
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space semicolon-->
pwd > ;
bash: syntax error near unexpected token `;'
pwd > ; ls
bash: syntax error near unexpected token `;'
pwd >> ; ls
bash: syntax error near unexpected token `;'
pwd >>> ; ls
bash: syntax error near unexpected token `>'
pwd >>>> ; ls
bash: syntax error near unexpected token `>>'
pwd >>>>> ; ls
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space DB_semicolon-->
pwd > ;;
bash: syntax error near unexpected token `;;'
pwd > ;; ls
bash: syntax error near unexpected token `;;'
pwd >> ;; ls
bash: syntax error near unexpected token `;;'
pwd >>> ;; ls
bash: syntax error near unexpected token `>'
pwd >>>> ;; ls
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space input-->
pwd > <
bash: syntax error near unexpected token `<'
pwd > < ls
bash: syntax error near unexpected token `<'
pwd >> < ls
bash: syntax error near unexpected token `<'
pwd >>> < ls
bash: syntax error near unexpected token `>'
pwd >>>> < ls
bash: syntax error near unexpected token `>>'
pwd >>>>> < ls
bash: syntax error near unexpected token `>>'
<!------------------>

<!-- space DB_input-->
pwd > <<
bash: syntax error near unexpected token `<<'
pwd > << ls
bash: syntax error near unexpected token `<<'
pwd >> << ls
bash: syntax error near unexpected token `<<'
pwd >>> << ls
bash: syntax error near unexpected token `>'
pwd >>>> << ls
bash: syntax error near unexpected token `>>'
pwd >>>>> << ls
bash: syntax error near unexpected token `>>'
<!------------------>