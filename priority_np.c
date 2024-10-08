#include <stdio.h>
#include <limits.h>

struct Process
{
    int pid;      // Process ID
    int at;       // Arrival Time
    int priority; // Higher value means higher priority
    int bt;       // Burst Time
    int st;       // Start Time
    int rem_time; // Remaining Time
    int ct;       // Completion Time
    float tat;    // Turnaround Time
    float wt;     // Waiting Time
    float rt;     // Response Time
};

int findNextJob(struct Process p[], int n, int curr_time, int isCompleted[])
{
    int idx = -1;
    int maxpriority = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        if (p[i].at <= curr_time && isCompleted[i] == 0)
        {
            if (p[i].priority > maxpriority)
            {
                maxpriority = p[i].priority;
                idx = i; // Update index of the process with the highest priority
            }
            else if (p[i].priority == maxpriority && p[i].at < p[idx].at)
            {
                idx = i; // If priorities are equal, choose the one that arrived first
            }
        }
    }
    return idx; // Return index of the next job
}

int main()
{
    int n;
    float swt = 0, srt = 0, stat = 0; // Initialize total sums
    float avgwt = 0, avgrt = 0, atat = 0;

    printf("Enter the number of Processes : ");
    scanf("%d", &n);
    struct Process p[n];

    // Input for each process
    for (int i = 0; i < n; i++)
    {
        printf("For process %d  : ", i + 1);
        p[i].pid = i + 1;
        printf("Enter AT, BT and Priority : ");
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].rem_time = p[i].bt; // Initialize remaining time
    }

    int currtime = 0;   // Current time initialization
    int completed = 0;  // Counter for completed processes
    int isCompleted[n]; // Array to track completion status
    for (int i = 0; i < n; i++)
    {
        isCompleted[i] = 0; // Initialize completion status
    }

    while (completed != n)
    {
        int idx = findNextJob(p, n, currtime, isCompleted);
        if (idx == -1)
        {
            currtime++; // Increment time if no process is available
        }
        else
        {
            // If the process starts for the first time
            if (p[idx].rem_time == p[idx].bt)
            {
                p[idx].st = currtime;              // Set start time
                p[idx].rt = p[idx].st - p[idx].at; // Response time
            }

            // Execute one unit of the process
            p[idx].rem_time--; // Decrement remaining time
            currtime++;        // Increment current time

            // Check if the process is completed
            if (p[idx].rem_time == 0)
            {
                p[idx].ct = currtime;               // Set completion time
                p[idx].tat = p[idx].ct - p[idx].at; // Calculate turnaround time
                p[idx].wt = p[idx].tat - p[idx].bt; // Calculate waiting time
                stat += p[idx].tat;                 // Accumulate turnaround time
                swt += p[idx].wt;                   // Accumulate waiting time
                srt += p[idx].rt;                   // Accumulate response time
                completed++;                        // Mark process as completed
                isCompleted[idx] = 1;               // Mark as completed
            }
        }
    }

    // Print results
    printf("\nPid\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    // Calculate and print averages
    avgwt = swt / n;
    avgrt = srt / n;
    atat = stat / n;

    printf("\nAverage Turnaround Time: %.2f", atat);
    printf("\nAverage Waiting Time: %.2f", avgwt);
    printf("\nAverage Response Time: %.2f\n", avgrt);

    return 0;
}