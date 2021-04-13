#include<stdio.h>

void gant(int order[], int start_time[], int end_time[],int size);

int main(){
	int i;
	int num = 5;//number of processes
	int process[num] = {1,2,3,4,5};
	int arrival[num] = {0,1,2,3,4};
	int burst[num]   = {4,3,1,5,2};
	int priority[num] = {2,3,4,5,5};		//	0 is lowest priority
	int size = sizeof(process)/sizeof(process[0]);
	int burst2[num];
	for(i=0;i<num;i++){
		burst2[i] = burst[i];
	}

	printf("\t\t-----------------------------------------------------------------------------------\n");
	printf("\t\t| \t  Process \t | \t Arrival \t | \t Burst \t | \tPriority  |\n");
	printf("\t\t-----------------------------------------------------------------------------------\n");
	
	for(i=0; i < num; i++){
	
	printf("\t\t| \t  P %d \t\t | \t %d \t\t | \t %d \t | \t %d \t  |\n",process[i],arrival[i],burst[i],priority[i]);
	printf("\t\t-----------------------------------------------------------------------------------\n");
	}

	//Solution
	int time=0;
	int j,k,current;
	int pr = -1;
	int start_time[size];
	int end_time[size];
	int order[size];
	float response=0;
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(time >= arrival[j]){
				if(priority[j] > pr && burst[j] > 0){
					pr = priority[j];
					current = j;
				}}}
				priority[j] = 0;
				order[i] = current;
				pr = -1;
				start_time[i] = time;
				response += (time - arrival[current]);
				time += burst[current];
				end_time[i] = time;
				burst[current] = 0;
	}
	
	//GANT CHART
	gant(order,start_time,end_time,size);
	
	int turn;
	int wait;
	float t=0;
	float w=0;
	int turnaround[size];
	int waiting[size];
	
	for(i=0;i<size;i++){
		turn = end_time[i] - arrival[i];
		turnaround[i] = turn;
		t += turnaround[i];
		wait = turnaround[i] - burst2[i];
		waiting[i] = wait;
		w += waiting[i];
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
