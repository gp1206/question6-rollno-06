#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<queue>
#include<algorithm>
using namespace std;

struct pro
{
	int pid, id, bt, art, completion_time, turnaround_time, waiting_time, status;				
}p[10];


bool comp(pro a, pro b)
{
	return a.bt< b.bt;
}

void display(int n)
{
	for(int i=0;i<n;i++)
	{
		printf("Process ID ",p[i].id,"Process Burst time: ",p[i].bt);
		printf("Process arrival time: ",p[i].art,"Process status: ",p[i].status);
	}
}
void findWaitingTime(pro proc[] ,int n ,int wt[])
{
    int rt[n];
    for (int i = 0; i < n; i++)
        { rt[i] = proc[i].bt;
        }
    int complete = 0, t = 0, minm = 0;
    int shortest = 0, finish_time;
    bool check = false;
    while (complete != n) 
	{
        for (int j = 0; j < n; j++) 
		{
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) 
			{
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }
        if (check == false) {
            t++;
            continue;
        }
        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
        {
        	minm = minm+1;
		}
        if (rt[shortest] == 0)
		 {
            complete++;
            finish_time = t + 1;
            wt[shortest] = finish_time -proc[shortest].bt -proc[shortest].art;
            if (wt[shortest] < 0)
            {
            	wt[shortest] = 0;
			}
        }
        t++;
    }
}
void findTurnAroundTime(pro proc[], int n,int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
    	tat[i] = proc[i].bt + wt[i];
	}
}
void findavgTime(pro proc[], int n)
{
    int wt[n], tat[n],total_tat = 0,total_wt = 0;
    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);
    printf("Processes");
    printf("Burst Time");
	printf("Waiting Time");
    printf("Turn Around Time");
    for (int i = 0; i < n; i++)
	 {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" "+proc[i].pid,"\t\t",proc[i].bt,"\t\t ",wt[i],"\t\t ",tat[i]);
     }
     printf("\nAverage waiting time = ",(float)total_wt / (float)n);
     printf("\nAverage turn around time = ", (float)total_tat / (float)n);
}
void show(queue <int> gq)
{
	queue <int> g = gq;
	while(!g.empty())
	{
		cout<<"\t"<<g.front();
		g.pop();
	}
printf("\n");
}
int main()
{
	int n,i,j,k;
	printf("Enter the number of processes:\n");
	scanf("%d",n);
	queue <int> o;		
	printf("Enter the arrival time of each process \n");
	for(i=0;i<n;i++)
	{
		printf("Enter the ariival time of P",i+1);
		scanf("%d",p[i].art);
		p[i].id = i+1;
	}
	printf("Enter the burst time of each process:\n");
	for(i=0;i<n;i++)
	{
		printf("Enter the burst time of P",i+1);
		scanf("%d",p[i].bt);
	}
	for(i=0;i<n;i++)
		p[i].status = 0;	
	sort(p, p+n, comp);
	int min = p[0].art;
	int loc;
	for(i=0;i<n;i++)
	{
		if(min > p[i].art)
			loc = i;
	}
	printf("Processing P",p[loc].id," for ",p[loc].bt," seconds");
	int time = p[loc].bt;
	p[loc].status = 1;
	p[loc].completion_time = time;
	o.push(p[loc].id);
	i=0;
	int process_count = 1;
	while(process_count!=n)
	{
		if(p[i].status!=1 && p[i].art <= time)
		{
			printf("Processing P",p[i].id," for ",p[i].bt," seconds");
			time += p[i].bt;
			o.push(p[i].id);
			p[i].status = 1;
			p[i].completion_time = time;
			process_count++;
		}
		i = (i+1)%n;
	}
	show(o);
	for(i=0;i<n;i++)
	{
		p[i].turnaround_time = p[i].completion_time - p[i].art;
	}
	
	for(i=0;i<n;i++)
	{
		p[i].waiting_time = p[i].turnaround_time - p[i].bt;
	}
	int sum = 0;
	for(i=0;i<n;i++)
	{
		sum+= p[i].turnaround_time;
	}
	printf("\nAverage turnaround time is ",sum);
	sum = 0;
	for(i=0;i<n;i++)
	{
		sum+= p[i].waiting_time;
	}
	printf("\nAverage waiting time is ",sum);
	return 0;
}
