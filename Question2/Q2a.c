#include <stdio.h>

struct Process {
    int id;     // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
    int rt;     // Response Time
};

// Function that will sort processes by arrival time
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

// Function that will implement First Come First Serve 
void fcfs(struct Process p[], int n) {
    int currentTime = 0;
    float totalTAT = 0, totalWT = 0, totalRT = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at)
            currentTime = p[i].at; // CPU idle until next process arrives

        p[i].rt = currentTime - p[i].at;
        p[i].wt = currentTime - p[i].at;
        currentTime += p[i].bt;
        p[i].ct = currentTime;
        p[i].tat = p[i].ct - p[i].at;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        totalRT += p[i].rt;
    }

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

int main() {
    int n = 4; // taken no of process as 4...if we want we can change it to user input
    struct Process p[4];

    printf("FIRST COME FIRST SERVE (FCFS) SCHEDULING\n");

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Sort by arrival time and run FCFS
    sortByArrival(p, n);
    fcfs(p, n);

    return 0;
}
