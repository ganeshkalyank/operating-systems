#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void fcfs(int request[], int head, int size) {
    int seek_count = 0;
    int distance;

    for (int i = 0; i < size; i++) {
        distance = abs(request[i] - head);
        seek_count += distance;
        head = request[i];

        printf("%d ", request[i]);
    }

    printf("\nTotal seek time: %d\n", seek_count);
}

void sstf(int request[], int head, int size) {
    int seek_count = 0;
    int distance;
    int min_distance;
    int min_index;

    for (int i = 0; i < size; i++) {
        min_distance = 999999;

        for (int j = 0; j < size; j++) {
            if (request[j] != -1) {
                distance = abs(request[j] - head);

                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }

        seek_count += min_distance;
        head = request[min_index];
        request[min_index] = -1;

        printf("%d ", head);
    }

    printf("\nTotal seek time: %d\n", seek_count);
}

void scan(int request[], int head, int size) {
    int seek_count = 0;
    int distance;
    int left = 0, right = size - 1;
    int direction = 1;

    for (int i = 0; i < size; i++) {
        if (request[i] <= head) {
            left = i;
        } else {
            right = i;
            break;
        }
    }

    while (left <= right) {
        if (direction == 1) {
            for (int i = right; i >= left; i--) {
                if (request[i] != -1) {
                    seek_count += abs(request[i] - head);
                    head = request[i];
                    request[i] = -1;

                    printf("%d ", head);
                }
            }

            direction = -1;
        } else {
            for (int i = left; i <= right; i++) {
                if (request[i] != -1) {
                    seek_count += abs(request[i] - head);
                    head = request[i];
                    request[i] = -1;

                    printf("%d ", head);
                }
            }

            direction = 1;
        }
    }

    printf("\nTotal seek time: %d\n", seek_count);
}

int main() {
    int request[MAX_SIZE], head, size;

    printf("Enter the number of requests: ");
    scanf("%d", &size);

    printf("Enter the requests: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\nFCFS:\n");
    fcfs(request, head, size);

    printf("\nSSTF:\n");
    sstf(request, head, size);

    printf("\nSCAN:\n");
    scan(request, head, size);

    return 0;
}
