#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

int frames[MAX_FRAMES];
int counter[MAX_FRAMES];
int pages[] = {1, 3, 0, 3, 5, 6, 3, 2, 5, 4, 7, 3, 1, 2, 4, 0};

void initializeFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }
}

int findLRUIndex() {
    int min = counter[0];
    int index = 0;
    for (int i = 1; i < MAX_FRAMES; i++) {
        if (counter[i] < min) {
            min = counter[i];
            index = i;
        }
    }
    return index;
}

int findLFUIndex() {
    int min = counter[0];
    int index = 0;
    for (int i = 1; i < MAX_FRAMES; i++) {
        if (counter[i] < min) {
            min = counter[i];
            index = i;
        }
    }
    return index;
}

int isPageInFrames(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1;
}

int findOptimalIndex(int start) {
    int index = -1;
    for (int i = 0; i < MAX_FRAMES; i++) {
        int frame = frames[i];
        int j;
        for (j = start; j < sizeof(pages) / sizeof(pages[0]); j++) {
            if (pages[j] == frame) {
                if (j > index) {
                    index = j;
                }
                break;
            }
        }
        if (j == sizeof(pages) / sizeof(pages[0])) {
            return i;
        }
    }
    return -1;
}

void printFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == -1) {
            printf("   ");
        } else {
            printf("%2d ", frames[i]);
        }
    }
    printf("||");
}

int main() {
    initializeFrames();

    int pageFaults_LRU = 0;
    int pageFaults_LFU = 0;
    int pageFaults_Optimal = 0;

    for (int i = 0; i < sizeof(pages) / sizeof(pages[0]); i++) {
        int page = pages[i];
        int lruIndex, lfuIndex;

        if (isPageInFrames(page) == -1) {
            pageFaults_LRU++;
            lruIndex = findLRUIndex();
            frames[lruIndex] = page;
            counter[lruIndex] = 0;

            pageFaults_LFU++;
            lfuIndex = findLFUIndex();
            frames[lfuIndex] = page;
            counter[lfuIndex] = 0;

            pageFaults_Optimal++;
            int optimalIndex = findOptimalIndex(i + 1);
            if (optimalIndex != -1) {
                frames[optimalIndex] = page;
            }
        }

        for (int j = 0; j < MAX_FRAMES; j++) {
            counter[j]++;
        }

        printFrames();
    }

    printf("\nPage Faults (LRU): %d\n", pageFaults_LRU);
    printf("Page Faults (LFU): %d\n", pageFaults_LFU);
    printf("Page Faults (Optimal): %d\n", pageFaults_Optimal);

    return 0;
}
