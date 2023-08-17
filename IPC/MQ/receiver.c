#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int mqid;
  key_t key;
  char txt[100];

  key = 1234;

  if ((mqid = msgget(key, 0666)) < 0) {
    perror("msgget error");
    exit(1);
  }

  while (1) {
    if (msgrcv(mqid,&txt,sizeof(txt),0,0) == -1) {
      perror("msgrcv error");
      exit(1);
    }
    
    printf("Received: %s\n",txt);
    
    if (strcmp(txt, "bye") == 0) {
      printf("Exiting...\n");
      break;
    }
  }

  return 0;
}
