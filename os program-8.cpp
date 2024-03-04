#include<stdio.h>  
int main()  
{  
    
    int i, processes, sum=0,cnt=0, y, q, wt=0, tat=0, at[10], bt[10], temp[10];  
    float avg_waitt, avg_turnat;  
    printf(" Total number of process in the system: ");  
    scanf("%d", &processes);  
    y = processes; 
for(i=0; i<processes; i++)  
{  
printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i+1);  
printf(" Arrival time is: \t");   
scanf("%d", &at[i]);  
printf(" \nBurst time is: \t");   
scanf("%d", &bt[i]);  
temp[i] = bt[i]; 
}  
 
printf("Enter the Time Quantum for the process: \t");  
scanf("%d", &q);   
printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");  
for(sum=0, i = 0; y!=0; )  
{  
if(temp[i] <= q && temp[i] > 0)    
{  
    sum = sum + temp[i];  
    temp[i] = 0;  
    cnt=1;  
    }     
    else if(temp[i] > 0)  
    {  
        temp[i] = temp[i] - q;  
        sum = sum + q;    
    }  
    if(temp[i]==0 && cnt==1)  
    {  
        y--; 
        printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i+1, bt[i], sum-at[i], sum-at[i]-bt[i]);  
        wt = wt+sum-at[i]-bt[i];  
        tat = tat+sum-at[i];  
        cnt =0;     
    }  
    if(i==processes-1)  
    {  
        i=0;  
    }  
    else if(at[i+1]<=sum)  
    {  
        i++;  
    }  
    else  
    {  
        i=0;  
    }  
}  

avg_waitt = wt * 1.0/processes;  
avg_turnat = tat * 1.0/processes;  
printf("\n Average Turn Around Time: \t%f", avg_waitt);  
printf("\n Average Waiting Time: \t%f", avg_turnat);  
 return 0;
 
}  
