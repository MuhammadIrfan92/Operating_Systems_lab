#include<stdio.h>

void min(int array[], int* minimum, int* ind,int size);
void gant(int order[],int time);
//void gant();

int main(){
	int i;
	int num = 4;//number of processes
	int process[num] = {1,2,3,4};
	int arrival[num] = {0,1,2,3};
	int burst[num]   = {8,4,9,5};
	int size = sizeof(arrival)/sizeof(arrival[0]);
	int arrival2[num];
	int burst2[num];
	for(i=0;i<size;i++){
		arrival2[i] = arrival[i];
		burst2[i] = burst[i];
	}

	printf("\t\t------------------------------------------------------------------\n");
	printf("\t\t| \t  Process \t | \t Arrival \t | \t Burst \t |\n");
	printf("\t\t------------------------------------------------------------------\n");
	
	for(i=0; i < num; i++){
	
	printf("\t\t| \t  P %d \t\t | \t %d \t\t | \t %d \t |\n",process[i],arrival[i],burst[i]);
	printf("\t\t------------------------------------------------------------------\n");
	}

	//Solution
	int minimum,ind;
	min(arrival,&minimum,&ind,num);
	int time = 0;
	int start_time[size];
	int end_time[size];
	int j;
	int order[100];
	int o=0;
	int rem[5];
	int min_ind,res;
	int ex[size] = {0,0,0,0};
	min_ind = ind;
	i = 0;
	int done = 0;
	while(done != 1){
		if(time < arrival[min_ind]){
			time += arrival[min_ind];
		}
		burst[min_ind]--;
		order[o++] = process[min_ind];
		time++;
		for(j=0;j<size;j++){
			if(time >= arrival[j] && j != min_ind){
				if(burst[j] < (burst[min_ind])){
					ex[min_ind] = time;
					min_ind = j;
					start_time[min_ind] = time;
				}
			}
		}
		if(burst[min_ind] == 0){
			end_time[min_ind] = time;
			arrival[min_ind] = 1000;
			burst[min_ind] = 1000;
			res = 1000;
			for(j=0;j<size;j++){
				if(time >= arrival[j]){
					if(burst[j] < res){
						res = burst[j];
						min_ind = j;
						start_time[min_ind] = time;
					}
				}
			}
		}
		if(res == 1000){
			done = 1;
		}
		i++;
	}
	gant(order,time);

	int waiting_time[size];
	float avg_wait = 0;
	for(i=0;i<size;i++){
		waiting_time[i] = start_time[i] - ex[i] - arrival2[i];
		avg_wait += waiting_time[i];
	}
	printf("Avg Waiting time is %0.2f\n",avg_wait/size);

	int turnaround_time[size];
	float avg_turn = 0;
	for(i=0;i<size;i++){
		turnaround_time[i] = end_time[i] - arrival2[i];
		avg_turn += turnaround_time[i];
	}
	printf("Avg Turn Around time is %0.2f\n",avg_turn/size);
	
	int prev[size];
	int pr=0;
	int pr1=0;
	float response = 0;
	int c=0;
	for(i=0;i<time;i++){
		if(i != 0){
			if(order[i] != order[i-1]){
				for(j=0;j<size;j++){
					if(prev[j] == order[i]){
						c = 1;
						}
					}
					if(c != 1){
						response += (i - arrival2[order[i]-1]);
						prev[pr++] = order[i];
					}
					else{
						c = 0;
					}
				}}
		else{
			prev[pr++] = order[0];
			response += (i - arrival2[order[i]-1]);
		}
	}
	printf("Average Response Time is %0.2f\n",response/size);	
	
}

void min(int array[], int* minimum, int* ind, int size){
	int i;
	*minimum = array[0];
	*ind = 0;
	for(i=0;i<size;i++){
		if(array[i] < *minimum){
			*minimum = array[i];
			*ind = i;
		}
	}
}

void gant(int order[],int size){
	
	printf("\n\n\t\t\t\t\tGANT CHART\n\n\n");
	int i;
	int prev = order[0];
	printf("\t\t-------%d\n",0);
	for(i=0 ; i < size ; i++){
		
		if(prev == order[i]){
//			printf("in IF i is %d and order[i] is %d\n",i,order[i]);
			printf("\t\t|  P%d  |\n",prev);
		}
		
		else{
			prev = order[i];
//			printf("in ELSE i is %d and order[i] is %d\n",i,order[i]);
			printf("\t\t-------%d\n",i);
			printf("\t\t|  P%d  |\n",prev);
		}
	}
	printf("\t\t-------%d\n",size);
}


