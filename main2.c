# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

char *cmd1[] = {"ls", NULL};
char *cmd2[] = {"head", NULL};
char *cmd3[] = {"wc", NULL};
char **cmds[] = {cmd1, cmd2, cmd3};
int cmd_n = 3;

void dopipes(int i) {
  pid_t ret;
  int pp[2] = {};
  if (i == cmd_n - 1) {
    // 左端なら単にexecvp
    execvp(cmds[0][0], cmds[0]);
  }
  else {
    // 左端以外ならpipeしてforkして親が実行、子が再帰
    pipe(pp);
    ret = fork();

    if (ret == 0) {
      // 子プロセスならパイプをstdoutにdup2してdopipes(i+1)で再帰し、
      // 次のforkで親になった側が右からi+1番目のコマンドを実行
      close(pp[0]);
      dup2(pp[1], 1);
      close(pp[1]);

      dopipes(i+1);
    }
    else {
      // 親プロセスならパイプをstdinにdup2して、
      // 右からi番目のコマンドを実行
      close(pp[1]);
      dup2(pp[0], 0);
      close(pp[0]);

      execvp(cmds[cmd_n-i-1][0], cmds[cmd_n-i-1]);
    }
  }
}

int main(void) {
  pid_t ret;

  ret = fork();
  if (ret == 0)
    dopipes(0);
  else
    wait(NULL);

  return 0;
}

__attribute__((destructor))
void end()
{
    system("leaks a.out");
}
