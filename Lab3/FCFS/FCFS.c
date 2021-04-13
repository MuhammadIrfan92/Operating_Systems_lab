#include<stdio.h>

void min(int array[], int* minimum, int* ind,int size);
void gant(int process[], int start_time[], int end_time[],int size);

int main(){
	int i;
	int num = 5;//number of processes
	int process[5] = {1,2,3,4,5};
	int arrival[5] = {4,6,0,6,5};
	int burst[5]   = {5,4,3,2,4};
	int size = sizeof(arrival)/sizeof(arrival[0]);

	printf("\t\t------------------------------------------------------------------\n");
	printf("\t\t| \t  Process \t | \t Arrival \t | \t Burst \t |\n");
	printf("\t\t------------------------------------------------------------------\n");
	
	for(i=0; i < num; i++){
	printf("\t\t| \t  P %d \t\t | \t %d \t\t | \t %d \t |\n",process[i],arrival[i],burst[i]);
	printf("\t\t------------------------------------------------------------------\n");
	}
	
	//Solution
	int time=0;
	int c,j;
	int start_time[5];
	int end_time[5];
	int p[5];
	float total_wait=0;
	float total_turnaround=0;
	float response=0;
	
	for(c=0; c < num; c++){
		
		int minimum,ind;
		min(arrival,&minimum,&ind,num);
		
		if(time < arrival[ind]){
			time = time + (arrival[ind] - time);
		}
		if(time >= arrival[ind]){
			start_time[c] = time;
			time = time + burst[ind];
		}
		p[c] = process[ind];
		end_time[c] = time; 
		response += time;
		int turnaround = time - arrival[ind];
		int wait = turnaround - burst[ind];
		total_wait += wait;
		total_turnaround += turnaround;
		arrival[ind] = 1000;
	}

	gant(p,start_time,end_time,size);
	printf("Average waiting time is %0.2f\n",total_wait/size);
	printf("Average response time is %0.2f\n",response/size);
	printf("Average turnaround time is %0.2f\n",total_turnaround/size);
}

void min(int array[], int* minimum, int* ind, int size){
	int i;
	*minimum = array[0];
	*ind = 0;
	for(i=0;i<size;i++){
		if((array[i] < *minimum)){
			*minimum = array[i];
			*ind = i;
		}
	}
}

void gant(int process[], int start_time[], int end_time[],int size){
	
	printf("\n\n\t\t\t\t\tGANT CHART\n\n\n");
	int i,j,k;
	int check = 0;

	for(i=0;i<size;i++){
		
		if((start_time[0] > 0) && check == 0){
			printf("-------- 0\n");
			for(j = 0; j < start_time[0]; j++){
				printf("| Free |\n");
			}
			check = 1;
		}
		
		if(i>=1){
			if((start_time[i] - end_time[i-1]) > 0){
				printf("-------- %d\n",end_time[i-1]);
				for(k=end_time[i-1];k<start_time[i];k++){
					printf("| Free |\n");
				}
			}
		}
		printf("-------- %d\n",start_time[i]);
		for(j=start_time[i];j<end_time[i];j++){
			printf("|  P%d  |\n",process[i]);
		}
		if(i == size-1){
			printf("-------- %d\n",end_time[i]);
		}
	}
}
