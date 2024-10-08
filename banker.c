#include <stdio.h>
#include <stdbool.h>
struct Process
{
    int max[10];
    int allocated[10];
    int need[10];
};
int n, r;
void takeInput(struct Process p[], int available[])
{
    for (int i = 0; i < n; i++)
    {
        printf("For process %d:", i + 1);
        printf("Enter the maximum resources need :");
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &p[i].max[j]);
        }
        printf("Enter the allocated resource :");
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &p[i].allocated[j]);
            p[i].need[j] = p[i].max[j] - p[i].allocated[j];
        }
    }
    printf("Enter Available Resource :");
    for (int i = 0; i < r; i++)
    {
        scanf("%d", &available[i]);
    }
}
void showtheinfo(struct Process p[])
{
    printf("\nPID\tMaximum\t\tAllocated\tNeed\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", i);
        for (int j = 0; j < r; j++)
            printf("%d ", p[i].max[j]);
        printf("\t\t");
        for (int j = 0; j < r; j++)
            printf("%d ", p[i].allocated[j]);
        printf("\t\t");
        for (int j = 0; j < r; j++)
            printf("%d ", p[i].need[j]);
        printf("\n");
    }
}
bool isSafeSequence(struct Process p[], int available[], int safeSequence[])
{
    bool finish[n];
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
    }
    bool proceed = true;
    while (proceed)
    {
        proceed = false;
        for (int i = 0; i < n; i++)
        {
            bool flag = true;
            if (finish[i] == false)
            {
                for (int j = 0; j < r; j++)
                {
                    if (p[i].need[j] <= available[j])
                        continue;
                    else
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag == false)
                    continue;
                for (int j = 0; j < r; j++)
                {
                    available[j] += p[i].allocated[j];
                }
                safeSequence[k++] = i;
                proceed = true;
                finish[i] = true;
            }
        }
    }
    if (k == n)
    {
        return true;
    }
    return false;
}
bool isSafeState(struct Process p[], int available[], int safeSequence[])
{
    if (isSafeSequence(p, available, safeSequence) == true)
    {
        return true;
    }
    else
        return false;
}
int main()
{
    printf("Enter the no. of Processes :");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter the no. of resources :");
    scanf("%d", &r);
    int available[r], safeSequence[n];
    takeInput(p, available);
    showtheinfo(p);
    printf("\n");
    if (isSafeState(p, available, safeSequence) == true)
    {
        printf("Safe sequence is :");
        for (int i = 0; i < n; i++)
        {
            printf("Process %d\n ", safeSequence[i]);
        }
    }
    else
    {
        printf("Unsafe sequence");
    }
}