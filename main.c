#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[], char **envp)
{
	int pipefd[2];
	pid_t cpid;
	char buf;

	(void)argc;
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0) {    /* Child reads from pipe */
		close(pipefd[1]);          /* Close unused write end */
		while (read(pipefd[0], &buf, 1) > 0)
			(void)write(STDERR_FILENO, &buf, 1);
		(void)write(STDERR_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	} else {            /* Parent writes argv[1] to pipe */
		close(pipefd[0]);          /* Close unused read end */
		dup2(pipefd[1], STDOUT_FILENO);
		if (execve("./foo", argv, envp) == -1)
			perror("execve");
		printf("execve FINISHED\n");
		close(pipefd[1]);          /* Reader will see EOF */
		wait(NULL);                /* Wait for child */
		exit(EXIT_SUCCESS);
	}
}
