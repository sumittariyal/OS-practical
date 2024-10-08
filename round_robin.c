#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int st;
    int ct;
    int rem_time;
    float tat;
    float wt;
    float rt;
};

// Compare function for sorting processes based on arrival time
int compare(const void *a, const void *b)
{
    int x = ((struct Process *)a)->at;
    int y = ((struct Process *)b)->at;
    return (x < y) ? -1 : 1;
}

int main()
{
    int n;
    printf("Enter the number of processes\n");
    scanf("%d", &n);

    struct Process p[n];
    int queue[n]; // To store the queue of process indices
    float swt = 0, stat = 0, srt = 0;
    float avgwt = 0, avgtat = 0, avgrt = 0;
    int vis[n];               // To track if a process is visited
    int front = 0, rare = -1; // Initialize queue front and rear

    for (int i = 0; i < n; i++)
    {
        vis[i] = 0; // Initialize visited array to 0
    }

    // Take process inputs
    for (int i = 0; i < n; i++)
    {
        printf("For process %d:\n", i + 1);
        p[i].pid = i + 1;
        printf("Enter Arrival Time (AT) and Burst Time (BT): ");
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].rem_time = p[i].bt; // Initialize remaining time
    }

    // Sort processes by arrival time
    qsort(p, n, sizeof(struct Process), compare);

    printf("Enter the time quantum\n");
    int qn;
    scanf("%d", &qn);

    int completed = 0;
    int curr_time = 0;

    // Add the first process (smallest arrival time) to the queue
    while (completed != n)
    {
        // Add all processes that have arrived by the current time to the queue
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= curr_time && vis[i] == 0)
            {
                rare++;
                queue[rare] = i;
                vis[i] = 1; // Mark as visited (added to queue)
            }
        }

        // If there are processes in the queue, process the front one
        if (front <= rare)
        {
            int index = queue[front];
            front++;

            // If the process is being executed for the first time
            if (p[index].bt == p[index].rem_time)
            {
                p[index].st = curr_time;
            }

            if (p[index].rem_time > qn)
            {
                curr_time += qn;
                p[index].rem_time -= qn;
            }
            else
            {
                curr_time += p[index].rem_time;
                p[index].rem_time = 0;
                completed++;

                p[index].ct = curr_time;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
                p[index].rt = p[index].st - p[index].at;

                swt += p[index].wt;
                stat += p[index].tat;
                srt += p[index].rt;
            }

            // Re-add the process to the queue if it's not finished
            if (p[index].rem_time > 0)
            {
                rare++;
                queue[rare] = index;
            }
        }
        else
        {
            // If no process is ready to execute, increment time
            curr_time++;
        }
    }

    // Calculate average times
    avgwt = swt / n;
    avgtat = stat / n;
    avgrt = srt / n;

    // Print results
    printf("\nPid\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Turnaround Time: %.2f", avgtat);
    printf("\nAverage Waiting Time: %.2f", avgwt);
    printf("\nAverage Response Time: %.2f", avgrt);

    return 0;
}