#include <stdio.h>

#define n 3
#define m 2

int detect_deadlock(int allocation[][m], int max[][m], int available[]) {
  int finished[n];
  for (int i = 0; i < n; i++) {
    finished[i] = 0;
  }

  while (1) {
    int all_finished = 1;
    for (int i = 0; i < n; i++) {
      if (!finished[i]) {
        all_finished = 0;
        break;
      }
    }

    if (all_finished) {
      return 0;
    }

    int found_process = 0;
    for (int i = 0; i < n; i++) {
      if (!finished[i]) {
        int can_finish = 1;
        for (int j = 0; j < m; j++) {
          if (max[i][j] - allocation[i][j] > available[j]) {
            can_finish = 0;
            break;
          }
        }

        if (can_finish) {
          finished[i] = 1;
          for (int j = 0; j < m; j++) {
            available[j] += allocation[i][j];
          }

          found_process = 1;
          break;
        }
      }
    }

    if (!found_process) {
      return 1;
    }
  }
}

int main() {
  int allocation[n][m] = {
    {0, 1},
    {2, 0},
    {3, 0},
  };

  int max[n][m] = {
    {7, 5},
    {3, 2},
    {9, 0},
  };

  int available[] = {3, 3};

  int deadlock = detect_deadlock(allocation, max, available);

  if (deadlock) {
    printf("Deadlock detected!");
  } else {
    printf("No deadlock detected.");
  }

  return 0;
}
