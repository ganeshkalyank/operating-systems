#include <stdio.h>
#include <unistd.h>

int main() {
  int even = 0, odd = 1;
  if (fork()>0) {
    while (1) {
      printf("Even: %d\n",even);
      even +=2;
      sleep(1);
    }
  } else {
    while (1) {
      printf("Odd: %d\n",odd);
      odd +=2;
      sleep(1);
    }
  }
  return 0;
}

