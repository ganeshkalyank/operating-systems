#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  int shmid;
  key_t key;
  char *shm, *s;

  key = 1234;

  if ((shmid = shmget(key,27,0666)) < 0) {
    perror("shmget error\n");
    exit(1);
  }
  
  if ((shm = shmat(shmid,NULL,0)) == (char *) -1) {
    perror("shmat error\n");
    exit(1);
  }

  for (s = shm; *s != '\0'; s++)
    putchar(*s);
  putchar('\n');

  *shm = '#';

  return 0;
}
