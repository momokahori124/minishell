
<!-- error -->
bash-3.2$ echo "a" ;; pwd
bash: syntax error near unexpected token `;;'
bash-3.2$ echo "a" ;;; pwd
bash: syntax error near unexpected token `;;'
bash-3.2$ echo "a" ;;;; pwd
bash: syntax error near unexpected token `;;'
bash-3.2$ echo "a" ;;>>;> pwd
bash: syntax error near unexpected token `;;'
<!-- ------- -->

<!--normal -->
bash-3.2$ pwd ;
/Users/jinichiro/Desktop/tmp/minishell
bash-3.2$ pwd ;;
bash: syntax error near unexpected token `;;'
bash-3.2$ pwd ;;;
bash: syntax error near unexpected token `;;'
<!-- ------- -->

<!--newline -->
bash-3.2$ echo "a" ;>
bash: syntax error near unexpected token `newline'
bash-3.2$ echo "a" ;>>
bash: syntax error near unexpected token `newline'
bash-3.2$ echo "a" ;>>>
bash: syntax error near unexpected token `>'
bash-3.2$ echo "a" ;>>>>
bash: syntax error near unexpected token `>>'
<!-- ------- -->

<!-- output -->
bash-3.2$ echo "a" ;> pwd
a
bash-3.2$ echo "a" ; > pwd
a
bash-3.2$ echo "a" ;>> pwd
a
bash-3.2$ echo "a" ; >> pwd
a
pwdのファイルもできる。中に書き込みはなし。

bash-3.2$ echo "a" ;>;> pwd
bash: syntax error near unexpected token `;'
bash-3.2$ echo "a" ;> ;> pwd
bash: syntax error near unexpected token `;'

bash-3.2$ echo "a" ;>>> pwd
bash: syntax error near unexpected token `>'
bash-3.2$ echo "a" ; >>> pwd
bash: syntax error near unexpected token `>'
bash-3.2$ echo "a" ;>>>> pwd
bash: syntax error near unexpected token `>>'
bash-3.2$ echo "a" ; >>>> pwd
bash: syntax error near unexpected token `>>'
<!-- ------------- -->

<!-- pipe -->
bash-3.2$ echo "a" ;| pwd
bash: syntax error near unexpected token `|'
bash-3.2$ echo "a" ;|| pwd
bash: syntax error near unexpected token `||'
bash-3.2$ echo "a" ;||| pwd
bash: syntax error near unexpected token `||'
bash-3.2$ echo "a" ; | pwd
bash: syntax error near unexpected token `|'
bash-3.2$ echo "a" ; || pwd
bash: syntax error near unexpected token `||'
bash-3.2$ echo "a" ; ||| pwd
bash: syntax error near unexpected token `||'
<!-- ------- -->

<!-- single_input -->
bash-3.2$ echo "a" ;< pwd
a
bash-3.2$ rm pwd
bash-3.2$ echo "a" ;< pwd
a
bash: pwd: No such file or directory
bash-3.2$ echo "a" ;<< pwd
> 読み込み待ちになる "<<"扱い
bash-3.2$ echo "a" ;<<< pwd
a "<<<"扱い
bash-3.2$ echo "a" ;<<<< pwd
bash: syntax error near unexpected token `<'
bash-3.2$ echo "a" ;<<<<< pwd
bash: syntax error near unexpected token `<<'

bash-3.2$ echo "a" ; < pwd
a
bash: pwd: No such file or directory
bash-3.2$ echo "a" ; << pwd
>
bash-3.2$ echo "a" ; <<< pwd
a
bash-3.2$ echo "a" ; <<<< pwd
bash: syntax error near unexpected token `<'
bash-3.2$ echo "a" ; <<<<< pwd
bash: syntax error near unexpected token `<<'
<!------------------>

<!-- space -->
bash-3.2$ echo "a" ; ; pwd
bash: syntax error near unexpected token `;'
bash-3.2$ echo "a" ; ;; pwd
bash: syntax error near unexpected token `;;'
bash-3.2$ echo "a" ; ;;; pwd
bash: syntax error near unexpected token `;;'
<!------------------>