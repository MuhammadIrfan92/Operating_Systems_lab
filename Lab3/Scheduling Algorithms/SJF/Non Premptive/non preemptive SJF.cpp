#include<stdio.h>

void min(int array[], int* minimum, int* ind,int size);
void gant(int end_time[], int start_time[],int order[],int size);


int main(){
	int i;
	int num = 4;//number of processes
	int process[num] = {1,2,3,4};
	int burst[num]   = {6,8,7,3};
	int size = sizeof(burst)/sizeof(burst[0]);

	printf("\t\t------------------------------------------\n");
	printf("\t\t| \t  Process \t | \t Burst \t |\n");
	printf("\t\t------------------------------------------\n");
	
	for(i=0; i < num; i++){
	
	printf("\t\t| \t  P %d \t\t | \t %d \t |\n",process[i],burst[i]);
	printf("\t\t------------------------------------------\n");
	}
	
	//Solution
	int time=0;
	int start_time[size];
	int end_time[size];
	int order[size];
	float turn=0;
	
	for(i=0 ; i < size ; i++){
		int minimum,ind;
		min(burst,&minimum,&ind,num);
		order[i] = ind;
		start_time[i] = time;
		time += burst[ind];
		end_time[i] = time;
		burst[ind] = 1000;
	}
	gant(end_time,start_time,order,size);
	float wait=0;
	for(i=0;i<size;i++){
		turn += end_time[i];
		wait += start_time[i];
	}
	printf("Avg waiting time is %0.2f\n",wait/size);
	printf("Avg Turn Around time is %0.2f\n",turn/size);
	//response time is waiting time when arrrival time is 0
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

void gant(int end_time[], int start_time[],int order[],int size){
	
	printf("\n\n\t\t\t\t\tGANT CHART\n\n\n");
	int i,j;
	for(i=0;i<size;i++){
		printf("\t\t-------- %d\n",start_time[i]);
		for(j=start_time[i];j<end_time[i];j++){
			printf("\t\t|  P%d  |\n",order[i]+1);
		}
	}
	printf("\t\t-------- %d\n",end_time[size-1]);
}
