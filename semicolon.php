
<!-- error -->
echo "a" ;; pwd
bash: syntax error near unexpected token `;;'
echo "a" ;;; pwd
bash: syntax error near unexpected token `;;'
echo "a" ;;;; pwd
bash: syntax error near unexpected token `;;'
echo "a" ;;>>;> pwd
bash: syntax error near unexpected token `;;'
<!-- ------- -->

<!--normal -->
pwd ;
/Users/jinichiro/Desktop/tmp/minishell
pwd ;;
bash: syntax error near unexpected token `;;'
pwd ;;;
bash: syntax error near unexpected token `;;'
<!-- ------- -->

<!--newline -->
echo "a" ;>
bash: syntax error near unexpected token `newline'
echo "a" ;>>
bash: syntax error near unexpected token `newline'
echo "a" ;>>>
bash: syntax error near unexpected token `>'
echo "a" ;>>>>
bash: syntax error near unexpected token `>>'
<!-- ------- -->

<!-- output -->
echo "a" ;> pwd
a
echo "a" ; > pwd
a
echo "a" ;>> pwd
a
echo "a" ; >> pwd
a
pwdのファイルもできる。中に書き込みはなし。

echo "a" ;>;> pwd
bash: syntax error near unexpected token `;'
echo "a" ;> ;> pwd
bash: syntax error near unexpected token `;'

echo "a" ;>>> pwd
bash: syntax error near unexpected token `>'
echo "a" ; >>> pwd
bash: syntax error near unexpected token `>'
echo "a" ;>>>> pwd
bash: syntax error near unexpected token `>>'
echo "a" ; >>>> pwd
bash: syntax error near unexpected token `>>'
<!-- ------------- -->

<!-- pipe -->
echo "a" ;| pwd
bash: syntax error near unexpected token `|'
echo "a" ;|| pwd
bash: syntax error near unexpected token `||'
echo "a" ;||| pwd
bash: syntax error near unexpected token `||'
echo "a" ; | pwd
bash: syntax error near unexpected token `|'
echo "a" ; || pwd
bash: syntax error near unexpected token `||'
echo "a" ; ||| pwd
bash: syntax error near unexpected token `||'
<!-- ------- -->

<!-- single_input -->
echo "a" ;< pwd
a
rm pwd
echo "a" ;< pwd
a
bash: pwd: No such file or directory


echo "a" ;<< pwd
> 読み込み待ちになる "<<"扱い
echo "a" ;<<< pwd
a "<<<"扱い
echo "a" ;<<<< pwd
bash: syntax error near unexpected token `<'
echo "a" ;<<<<< pwd
bash: syntax error near unexpected token `<<'

echo "a" ; < pwd
a
bash: pwd: No such file or directory
echo "a" ; << pwd
>
echo "a" ; <<< pwd
a
echo "a" ; <<<< pwd
bash: syntax error near unexpected token `<'
echo "a" ; <<<<< pwd
bash: syntax error near unexpected token `<<'
<!------------------>

<!-- space -->
echo "a" ; ; pwd
bash: syntax error near unexpected token `;'
echo "a" ; ;; pwd
bash: syntax error near unexpected token `;;'
echo "a" ; ;;; pwd
bash: syntax error near unexpected token `;;'
<!------------------>

echo "a" < ppp
bash: ppp: No such file or directory
echo "a" ;< ppp
a
bash: ppp: No such file or directory