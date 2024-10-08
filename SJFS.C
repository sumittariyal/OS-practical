#include<stdio.h>
struct Process{
    int pid;
    int at;
    int bt;
    int st;
    int ct;
    float tat;
    float wt;
    float rt;
};
int findNextProcess(struct Process p[],int n, int curr_time,int is_completed[])
{
    int idx = -1;
    int min_bt=100000;
    for(int i = 0;i < n;i++)
    {
        if(p[i].at <= curr_time && is_completed[i] == 0)
        {
            if(p[i].bt < min_bt)
            {

                {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
            else if(p[i].bt == min_bt && p[i].at < p[idx].at){
                     idx = i;
                }
                
            }
        }
    return idx;
}
int main()
{
    int n;
    float swt = 0,stat = 0,srt = 0;
    float avgwt = 0, avgtat = 0, avgrt = 0;
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    struct Process p[n];
    for(int i = 0;i < n;i++)
    {
        printf("For process %d : ",i+1);
        p[i].pid = i+1;
        printf("Enter the AT and BT : ");
        scanf("%d%d",&p[i].at,&p[i].bt);
    }
    int completed_process = 0;
    int currenttime = 0;
    int isCompleted[n];
    for(int i = 0;i < n;i++)
    {
        isCompleted[i]=0;
    }
    while(completed_process != n)
    {
        int idx = findNextProcess( p,n,currenttime,isCompleted);;
        if(idx != -1)
        {
            p[idx].st = currenttime;
            p[idx].ct = p[idx].st + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].st - p[idx].at;
            stat += p[idx].tat;
            swt  += p[idx].wt;
            srt += p[idx].rt;
            currenttime=p[idx].ct;
            completed_process++;
            isCompleted[idx]=1;
        }
        else{
            currenttime++;
        }
    }
    avgwt = swt / n;
    avgtat = stat / n;
    avgrt = srt / n;
     printf("\nPid\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    // Print average values
    printf("\nAverage Turnaround Time: %.2f", avgtat);
    printf("\nAverage Waiting Time: %.2f", avgwt);
    printf("\nAverage Response Time: %.2f", avgrt);

}