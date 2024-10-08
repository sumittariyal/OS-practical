#include <stdio.h>
#include <limits.h>
struct Process
{
    int pid;
    int at;
    int priority;
    int bt;
    int st;
    int ct;
    float tat;
    float wt;
    float rt;
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
                idx = i;
            }
            else if (p[i].priority == maxpriority && p[i].at < p[idx].at)
            {
                idx = i;
            }
        }
    }
    return idx;
}
int main()
{
    int n;
    float swt = 0, srt = 0, stat = 0;
    float avgwt = 0, avgrt = 0, atat = 0;
    printf("Enter the number of Processes :");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("For process %d  : ", i + 1);
        p[i].pid = i + 1;
        printf("Enter AT,BT and Priority :");
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].priority);
    }
    int currtime = 0;
    int completed = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++)
    {
        isCompleted[i] = 0;
    }
    while (completed != n)
    {
        int idx = findNextJob(p, n, currtime, isCompleted);
        if (idx == -1)
        {
            currtime++;
        }
        else
        {
            p[idx].st = currtime;
            p[idx].ct = p[idx].st + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].st - p[idx].at;
            stat += p[idx].tat;
            swt += p[idx].wt;
            srt += p[idx].rt;
            completed++;
            isCompleted[idx] = 1;
            currtime = p[idx].ct;
        }
    }
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
}