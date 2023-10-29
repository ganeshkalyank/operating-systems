#include <stdio.h>

#define P 5
#define R 3

void isSafe(int processes[], int max[][R], int allocation[][R], int available[]) {
  int finish[P] = {0};
  int work[R];

  for (int i = 0; i < R; i++) {
    work[i] = available[i];
  }

  int count = 0;
  while (count < P) {
    int found = 0;
    for (int i = 0; i < P; i++) {
      if (!finish[i]) {
        int j;
        for (j = 0; j < R; j++) {
          if (max[i][j] - allocation[i][j] > work[j]) {
            break;
          }
        }

        if (j == R) {
          finish[i] = 1;
          count++;

          for (int k = 0; k < R; k++) {
            work[k] += allocation[i][k];
          }

          found = 1;
          break;
        }
      }
    }

    if (!found) {
      printf("The system is not in a safe state.\n");
      return;
    }
  }

  printf("The system is in a safe state.\n");
}

int main() {
  int processes[] = {0, 1, 2, 3, 4};
  int max[][R] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
  int allocation[][R] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
  int available[] = {3, 3, 2};

  isSafe(processes, max, allocation, available);

  return 0;
}
