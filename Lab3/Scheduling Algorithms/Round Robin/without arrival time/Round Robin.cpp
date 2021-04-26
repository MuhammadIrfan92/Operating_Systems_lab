#include<stdio.h>

void gant(int order[], int start_time[], int end_time[],int size);

int main(){
	int i;
	int num = 3;//number of processes
	int process[num] = {1,2,3};
	int arrival[num] = {0,0,0};
	int burst[num]   = {24,3,3};
	int size = sizeof(process)/sizeof(process[0]);
	int burst2[num];
	for(i=0;i<num;i++){
		burst2[i] = burst[i];
		
	}

	printf("\t\t------------------------------------------\n");
	printf("\t\t| \t  Process \t | \t Burst \t |\n");
	printf("\t\t------------------------------------------\n");
	
	for(i=0; i < num; i++){
	
	printf("\t\t| \t  P %d \t\t | \t %d \t |\n",process[i],burst[i]);
	printf("\t\t------------------------------------------\n");
	}
	
	//Solution
	int time=0;
	int end_time[size];
	int m=0;
	int quantum = 4;
	int order[100]={-1};
	int t1[100];
	int t2[100];
	int count = 0;
	int k,j;
	int done = 0;
	i = 0;
		
	while(done != 1){
		
		if(burst[m] >= quantum){
			t1[i] = time;
			time += quantum;
			t2[i] = time;
			burst[m] -= quantum;
			order[i] = m;
			end_time[m] = time;
			i++;
		}
		else{
			if(burst[m] != 0){
				t1[i] = time;
				time += burst[m];
				t2[i] = time;
				burst[m] = 0;
				order[i] = m;
				end_time[m] = time;
				i++;
			}
		}
		m++;
		if(m == 3){
			m = m%3;
		}
		count = 0;
		for(k=0;k<size;k++){
			if(burst[k] == 0){
				count++;
			}
		}
		if(count == size){
			done = 1;
		}
	}
	
	//GANT CHART
	gant(order,t1,t2,i);

	int turn;
	int wait;
	float t=0;
	float w=0;
	int turnaround[size];
	int waiting[size];
	float response = 0;
	
	for(i=0;i<size;i++){
		turn = end_time[i] - arrival[i];
		turnaround[i] = turn;
		t += turnaround[i];
		wait = turnaround[i] - burst2[i];
		waiting[i] = wait;
		w += waiting[i];
		response += t1[i];
	}
	printf("\n\n");
	printf("Avg Turn Around time is %0.2f\n",t/size);
	printf("Avg Waiting time is %0.2f\n",w/size);
	printf("Avg Response time is %0.2f\n",response/size);
}


void gant(int order[], int start_time[], int end_time[],int size){
	
	printf("\n\n\t\t\t\t\tGANT CHART\n\n\n");
	int i,j,k;
	int check = 0;

	for(i=0;i<size;i++){
		printf("------- %d\n",start_time[i]);
		for(j=start_time[i];j<end_time[i];j++){
			printf("|  P%d  |\n",order[i]+1);
		}
	}
	printf("------- %d\n",end_time[size-1]);
}
