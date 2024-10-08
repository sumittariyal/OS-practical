#include<stdio.h>
#include<limits.h>
struct Process{
    int pid;
    int at;
    int bt;
    int st;
    int ct;
    int rt;
    float tat;
    float wt;
    float rt_t;
};
int findShortestProcess(struct Process p[],int n,int curr_time,int isCompleted[])
{
  int idx = -1;
  int min_remaining_time = INT_MAX;
  for(int i = 0;i < n;i++)
  {
    if(p[i].at <= curr_time && isCompleted[i]==0)
    {
      if(p[i].rt < min_remaining_time)
      {
        min_remaining_time = p[i].rt;
      idx = i;
      }
      else if(p[i].rt == min_remaining_time && p[i].at < p[idx].at)
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
  float swt = 0, stat = 0, srt = 0;
  float avgwt = 0,avgtat = 0,avgrt = 0;
  printf("Enter the number of process :");
  scanf("%d",&n);
  struct Process p[n];
  for(int i = 0;i < n;i++)
  {
    printf("For process %d :",i+1);
    p[i].pid = i+1;
    printf("Enter the At and BT : ");
    scanf("%d%d",&p[i].at,&p[i].bt);
    p[i].rt = p[i].bt;
   
  }
  int completed = 0;
  int current_time = 0;
  int isCompleted[n];
  for(int i = 0;i  <n ;i++)
  {
    isCompleted[i]=0;
  }

  while(completed != n)
  {
      int idx = findShortestProcess(p,n,current_time,isCompleted);
      if(idx == -1)
      {
         current_time++;
      }
      else{
       if(p[idx].rt == p[idx].bt)
       {
          p[idx].st = current_time;
          p[idx].rt_t = p[idx].st-p[idx].at;
       }
        p[idx].rt--;
         current_time++;
      
         if(p[idx].rt == 0)
         {
           p[idx].ct = current_time;
           p[idx].tat = p[idx].ct - p[idx].at;
           p[idx].wt = p[idx].tat - p[idx].bt;
           stat += p[idx].tat;
           swt += p[idx].wt;
           srt += p[idx].rt_t;

           isCompleted[idx]=1;
           completed++;
         }

      }
  }
      avgwt = swt/n;
      avgrt = srt/n;
      avgtat = stat/n;
        printf("\nPid\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Turnaround Time: %.2f", avgtat);
    printf("\nAverage Waiting Time: %.2f", avgwt);
    printf("\nAverage Response Time: %.2f", avgrt);
  

  
}// SRTF