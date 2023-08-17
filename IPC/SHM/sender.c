#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  int shmid;
  key_t key;
  char *shm, *s;
  key = 1234;
  char c;

  if ((shmid = shmget(key, 27, IPC_CREAT | 0666)) < 0) {
    perror("shmget error\n");
    exit(1);
  }

  if ((shm = shmat(shmid, NULL,0)) == (char *) -1) {
    perror("shmat error\n");
    exit(1);
  }

  s = shm;
  for (c = 'a'; c <= 'z'; c++)
    *s++ = c;
  *s = '\0';

  printf("waiting for receiver...\n");

  while (*shm != '#')
    sleep(10);

  return 0;
}
