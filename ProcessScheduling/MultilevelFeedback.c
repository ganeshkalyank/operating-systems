#include <stdio.h>
#include <stdlib.h>

struct Process {
    int process_id;
    int burst_time;
    int priority;
};

struct Queue {
    struct Process* items;
    int front, rear, capacity;
};

struct Process createProcess(int process_id, int burst_time, int priority) {
    struct Process p;
    p.process_id = process_id;
    p.burst_time = burst_time;
    p.priority = priority;
    return p;
}

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->items = (struct Process*)malloc(capacity * sizeof(struct Process));
    return queue;
}

int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

int isFull(struct Queue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

void enqueue(struct Queue* queue, struct Process process) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
    } else {
        if (isEmpty(queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->rear = (queue->rear + 1) % queue->capacity;
        }
        queue->items[queue->rear] = process;
    }
}

struct Process dequeue(struct Queue* queue) {
    struct Process emptyProcess;
    emptyProcess.process_id = -1;
    emptyProcess.burst_time = -1;
    emptyProcess.priority = -1;

    if (isEmpty(queue)) {
        return emptyProcess;
    } else {
        struct Process process = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % queue->capacity;
        }
        return process;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Queue* queue1 = createQueue(100);
    struct Queue* queue2 = createQueue(100);
    struct Queue* queue3 = createQueue(100);

    for (int i = 0; i < n; i++) {
        int process_id, burst_time, priority;
        printf("Enter details for Process %d\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &process_id);
        printf("Burst Time: ");
        scanf("%d", &burst_time);
        printf("Priority (1, 2, or 3): ");
        scanf("%d", &priority);

        struct Process p = createProcess(process_id, burst_time, priority);
        if (priority == 1) {
            enqueue(queue1, p);
        } else if (priority == 2) {
            enqueue(queue2, p);
        } else if (priority == 3) {
            enqueue(queue3, p);
        }
    }

    int time_quantum_q1 = 2;
    int remaining_burst_time_q1 = 0;

    while (!isEmpty(queue1) || !isEmpty(queue2) || !isEmpty(queue3)) {
        if (!isEmpty(queue1)) {
            struct Process p = dequeue(queue1);
            if (remaining_burst_time_q1 == 0) {
                remaining_burst_time_q1 = time_quantum_q1;
            }
            if (p.burst_time <= remaining_burst_time_q1) {
                printf("Process %d executed from Queue 1 with time %d\n", p.process_id, p.burst_time);
                remaining_burst_time_q1 -= p.burst_time;
            } else {
                printf("Process %d executed from Queue 1 with time %d\n", p.process_id, remaining_burst_time_q1);
                p.burst_time -= remaining_burst_time_q1;
                enqueue(queue2, p);
                remaining_burst_time_q1 = 0;
            }
        }

        if (!isEmpty(queue2)) {
            struct Process p = dequeue(queue2);
            printf("Process %d executed from Queue 2 with time %d\n", p.process_id, p.burst_time);
        }

        if (!isEmpty(queue3)) {
            struct Process p = dequeue(queue3);
            printf("Process %d executed from Queue 3 with time %d\n", p.process_id, p.burst_time);
        }
    }

    free(queue1->items);
    free(queue2->items);
    free(queue3->items);
    free(queue1);
    free(queue2);
    free(queue3);

    return 0;
}
