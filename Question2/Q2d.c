#include <stdio.h>
struct Process {
    int id;         // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int remt;       // Remaining Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int rt;         // Response Time
    int started;    // To track first execution (for response time)
};
// Sort by Arrival Time
void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
// Round Robin Scheduling
void roundRobin(struct Process p[], int n, int tq) {
    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0, totalRT = 0;

    // Initialize remaining time and flags
    for (int i = 0; i < n; i++) {
        p[i].remt = p[i].bt;
        p[i].started = 0;
    }
    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].remt > 0) {
                // Response time (first time CPU executes process)
                if (p[i].started == 0) {
                    p[i].rt = currentTime - p[i].at;
                    p[i].started = 1;
                    totalRT += p[i].rt;
                }

                // If remaining time > time quantum
                if (p[i].remt > tq) {
                    p[i].remt -= tq;
                    currentTime += tq;
                } else {
                    // Process finishes
                    currentTime += p[i].remt;
                    p[i].remt = 0;
                    p[i].ct = currentTime;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    totalTAT += p[i].tat;
                    totalWT += p[i].wt;

                    completed++;
                }
                executed = 1;
            }
        }

        // If no process was executed in this cycle (CPU idle)
        if (!executed)
            currentTime++;
    }

    // Print table
    printf("\n%-10s%-10s%-10s%-15s%-15s%-10s%-10s\n",
           "Process", "Arrival", "Burst", "Completion", "Turnaround", "Waiting", "Response");

    for (int i = 0; i < n; i++) {
        printf("P%-9d%-10d%-10d%-15d%-15d%-10d%-10d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Response Time: %.2f\n", totalRT / n);
}

// Main Function
int main() {
    int n = 4; // fixed as per professor
    int tq;    // time quantum
    struct Process p[4];

    printf("ROUND ROBIN (RR) SCHEDULING\n");

    // Take input
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    sortByArrival(p, n);
    roundRobin(p, n, tq);

    return 0;
}