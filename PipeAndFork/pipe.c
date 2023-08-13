#include <stdio.h>
#include <unistd.h>

int main() {
  int p[2];
  char inbuff[10],outbuff[10];
  if(pipe(p)<0) {
    printf("Pipe creation failed!\n");
    return 0;
  } else {
    printf("Pipe created!\n");
  }
  if (fork() > 0) {
    printf("Parent says 'Enter some text': ");
    scanf("%s",inbuff);
    write(p[1],inbuff,10);
    sleep(2);
    printf("Killing parent\n");
  } else {
    read(p[0],outbuff,10);
    printf("Child received: %s\n",outbuff);
    sleep(2);
    printf("Killing child\n");
  }
  return 0;
}
