
#include <stdlib.h>
struct Process
{
    int pid;
    int at;
    int bt;
    int st;
    int ct;
    float tat;
    float wt;
    float rt;
};
int main()
{
    int n;
    float swt = 0, stat = 0;
    float cu = 0, throughput = 0, srt = 0;
    float avgwt = 0, avgtat = 0, avgrt = 0;
    float sbt = 0;
    printf("\nName : Sumit Tariyal\nSection - A2\nRoll No.- 69\n\n");
    printf("Enter the number of Processes :");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("For Process %d ", i + 1);
        p[i].pid = i + 1;
        printf("Enter the value of AT and BT : ");
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    int currTime = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++)
    {
        isCompleted[i] = 0;
    }
    int completed = 0;

    while (completed != n)
    {
        int idx = -1;
        int minArrival = 1e9;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currTime && isCompleted[i] == 0)
            {
                if (p[i].at < minArrival)
                {
                    idx = i;
                    minArrival = p[i].at;
                }
            }
        }
        if (idx == -1)
        {
            currTime++;
        }
        else
        {
            p[idx].st = currTime;
            p[idx].ct = p[idx].st + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].rt = p[idx].st - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            stat += p[idx].tat;
            swt += p[idx].wt;
            srt += p[idx].rt;
            isCompleted[idx] = 1;
            completed++;
            currTime = p[idx].ct;
        }
    }

    avgwt = swt / n;
    avgrt = srt / n;
    avgtat = stat / n;
    printf("\nPid\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Turnaround Time: %.2f", avgtat);
    printf("\nAverage Waiting Time: %.2f", avgwt);
    printf("\nAverage Response Time: %.2f", avgrt);
}