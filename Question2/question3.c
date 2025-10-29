#include <stdio.h>
struct Process {
    int id;         // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int pr;         // Priority (lower number = higher priority)
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int rt;         // Response Time
    int completed;  // Completion flag
};
// Sort processes by Arrival Time
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
// Priority Scheduling (Non-Preemptive)
void priorityScheduling(struct Process p[], int n) {
    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0, totalRT = 0;
    for (int i = 0; i < n; i++)
        p[i].completed = 0;
    while (completed < n) {
        int highestPriority = -1;
        int minPriority = 9999;
        // Find process with highest priority (lowest priority number)
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].completed == 0) {
                if (p[i].pr < minPriority) {
                    minPriority = p[i].pr;
                    highestPriority = i;
                }
            }
        }
        // If no process has arrived yet, increment time
        if (highestPriority == -1) {
            currentTime++;
            continue;
        }
        // Execute selected process
        p[highestPriority].rt = currentTime - p[highestPriority].at;
        p[highestPriority].wt = currentTime - p[highestPriority].at;
        currentTime += p[highestPriority].bt;
        p[highestPriority].ct = currentTime;
        p[highestPriority].tat = p[highestPriority].ct - p[highestPriority].at;
        p[highestPriority].completed = 1;

        totalTAT += p[highestPriority].tat;
        totalWT += p[highestPriority].wt;
        totalRT += p[highestPriority].rt;

        completed++;
    }
    // Table header
    printf("\n%-10s%-10s%-10s%-10s%-15s%-15s%-10s%-10s\n",
           "Process", "Arrival", "Burst", "Priority", "Completion", "Turnaround", "Waiting", "Response");
    // Display each process
    for (int i = 0; i < n; i++) {
        printf("P%-9d%-10d%-10d%-10d%-15d%-15d%-10d%-10d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    // Averages
    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Response Time: %.2f\n", totalRT / n);
}
// Main function
int main() {
    int n = 4; // Fixed number of processes
    struct Process p[4];

    printf("PRIORITY SCHEDULING (NON-PREEMPTIVE)\n");

    // Take input for 4 processes
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter Arrival Time, Burst Time and Priority for Process P%d: ", p[i].id);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
    }

    sortByArrival(p, n);
    priorityScheduling(p, n);

    return 0;
}