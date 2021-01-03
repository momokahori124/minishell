# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(-1);
	} else if (pid == 0) {
		// 子プロセスで別プログラムを実行
		puts("Failed to \033[4mread\033[0m aaaa");
		puts("Failed to \033[1mread\033[0m aaaa");
		execlp("echo", "echo", "abc", "def", NULL);
		// perror("echo");
		// exit(-1);
	}

	// 親プロセス
	int status;
	pid_t r = waitpid(pid, &status, 0); //子プロセスの終了待ち
	if (r < 0) {
		perror("waitpid");
		exit(-1);
	}
	if (WIFEXITED(status)) {
		// 子プロセスが正常終了の場合
		printf("child exit-code=%d\n", WEXITSTATUS(status));
	} else {
		printf("child status=%04x\n", status);
	}
	return 0;
}
