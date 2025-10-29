#include <stdio.h>
struct Process {
    int id;     // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
    int rt;     // Response Time
    int completed; // Flag to check if process is done
};
// Function to sort processes by arrival time
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
// Function to implement SJF (Non-Preemptive)
void sjf(struct Process p[], int n) {
    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0, totalRT = 0;

    for (int i = 0; i < n; i++)
        p[i].completed = 0;

    while (completed < n) {
        int shortest = -1;
        int minBurst = 9999;
        // Find process with shortest burst time among those that have arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].completed == 0) {
                if (p[i].bt < minBurst) {
                    minBurst = p[i].bt;
                    shortest = i;
                }
            }
        }
        // If no process has arrived yet
        if (shortest == -1) {
            currentTime++;
            continue;
        }
        // Process execution
        p[shortest].rt = currentTime - p[shortest].at;
        p[shortest].wt = currentTime - p[shortest].at;
        currentTime += p[shortest].bt;
        p[shortest].ct = currentTime;
        p[shortest].tat = p[shortest].ct - p[shortest].at;
        p[shortest].completed = 1;

        totalTAT += p[shortest].tat;
        totalWT += p[shortest].wt;
        totalRT += p[shortest].rt;
        completed++;
    }

    // Aligned table header
    printf("\n%-10s%-10s%-10s%-15s%-15s%-10s%-10s\n",
           "Process", "Arrival", "Burst", "Completion", "Turnaround", "Waiting", "Response");

    // Display all processes
    for (int i = 0; i < n; i++) {
        printf("P%-9d%-10d%-10d%-15d%-15d%-10d%-10d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt, p[i].rt);
    }

    // Display average times
    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Response Time: %.2f\n", totalRT / n);
}

// Main function
int main() {
    int n = 4; // Fixed number of processes
    struct Process p[4];

    printf("SHORTEST JOB FIRST (SJF) NON-PREEMPTIVE SCHEDULING\n");

    // Take input for 4 processes
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    sortByArrival(p, n);
    sjf(p, n);

    return 0;
}