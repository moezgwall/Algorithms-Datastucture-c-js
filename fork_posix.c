#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

 // 0 for reading 
 // 1 for writing 

int main(void) {
  pid_t pid;
  int status;
  int fd[2]; 
  if (pipe(fd) == -1) {
    perror("pipe failed");
    return 1;
  }
  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    printf("child start ...\n");
    close(fd[0]);
    sleep(5);
    const char *data = "hello my parent";
    write(fd[1], data, strlen(data) + 1);
    close(fd[1]);
    exit(0);
  }
 
  close(fd[1]);
  pid_t cpid = waitpid(pid, &status, 0);
  printf(" [child: %d] waited for 5 seconds,status : %d \n ", cpid, status);
  char buffer[128] = {0};
  ssize_t bytes = read(fd[0], buffer, sizeof(buffer) - 1);
  if (bytes > 0) {
    printf("[parent: %d ] Retrieved from pipe: \"%s\"\n",pid, buffer);
  }

  close(fd[0]);

  return 0;
}
