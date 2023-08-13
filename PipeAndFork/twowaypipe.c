#include <stdio.h>
#include <unistd.h>

int main() {
  int p1[2],p2[2];
  char inbuff[10],outbuff[10];
  pipe(p1); pipe(p2);
  if (fork()>0) {
    printf("Send from parent: ");
    scanf("%s", inbuff);
    write(p1[1], inbuff, 10);
    read(p2[0], outbuff, 10);
    printf("Parent received: %s\n",outbuff);
    sleep(2);
  } else {
    printf("Send from child: ");
    scanf("%s", inbuff);
    write(p2[1], inbuff, 10);
    read(p1[0], outbuff, 10);
    printf("Child received: %s\n",outbuff);
    sleep(2);
  }
  return 0;
}
