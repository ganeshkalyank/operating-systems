#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int mqid;
  key_t key;
  char txt[100];
    
  key = 1234;

  if ((mqid = msgget(key, IPC_CREAT | 0666)) < 0) {
    perror("msgget error");
    exit(1);
  }

  while (1) {
    printf("Enter something: ");
    scanf("%s",txt);

    if (msgsnd(mqid, &txt, strlen(txt), 0) == -1) {
      perror("msgsnd error");
      exit(1);
    }

    if (strcmp(txt,"bye") == 0) {
      printf("Exiting... \n");
      break;
    }
  }

  return 0;
}
