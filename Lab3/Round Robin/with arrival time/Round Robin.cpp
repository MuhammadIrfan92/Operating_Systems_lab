#include<stdio.h>

void gant(int order[],int size);

int main(){
	int i=0;
	int num = 5;//number of processes
	int process[num] = {1,2,3,4,5};
	int arrival[num] = {0,1,2,3,4};
	int burst[num]   = {5,3,1,2,3};
	int size = sizeof(arrival)/sizeof(arrival[0]);
	int burst2[num];
	for(i=0;i<num;i++){
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
	int quantum = 0;//2
	int time=0;
	int j,k;
	int end_time[5];
	int ready[size] = {-1,-1,-1,-1,-1};
	int c = 0;
	int temp;
	int done = 0;
	int count;
	int order[100] = {-1};
	int o=0;
	i=0;
	while(done != 1){
		for(j=0;j<size;j++){		// Checking if new process arrives then add in the array
			if(time == arrival[j]){
				ready[c++] = j;
			}}
			if(quantum == 2 || burst[ready[0]] == 0){	//if time quantum is reached or burst == 0 change process
				end_time[ready[0]] = time;
				quantum = 0;
				temp = ready[0];
				for(k=0;k<size;k++){			//moving elements to the left
					ready[k] = ready[k+1];
				}
				c --;
				if(burst[temp] > 0){			//add current process only if burst > 0 
					ready[c++] = temp;
				}
			}
			if(c >= size){
				c = size;
			}
			time++;
			burst[ready[0]]--;
			quantum++;
			order[o++] = ready[0]+1;
			count = 0;
			for(k=0;k<size;k++){
				if(burst[k] == 0){
					count++;
				}
			}
			if(count == size){
				end_time[ready[0]] = time;
				done = 1;
			}
			i++;
		}
		//GANT CHART
		gant(order,time);
		
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
		
		int prev[size];
	int pr=0;
	int pr1=0;
	float response = 0;
	int c1=0;
	for(i=0;i<time;i++){
		if(i != 0){
			if(order[i] != order[i-1]){
				for(j=0;j<size;j++){
					if(prev[j] == order[i]){
						c1 = 1;
						}
					}
					if(c1 != 1){
						response += (i - arrival[order[i]-1]);
						prev[pr++] = order[i];
					}
					else{
						c1 = 0;
					}
				}}
		else{
			prev[pr++] = order[0];
			response += (i - arrival[order[i]-1]);
		}
	}
	printf("Average Response Time is %0.2f\n",response/size);	
}

void gant(int order[],int size){
	
	printf("\n\n\t\t\t\t\tGANT CHART\n\n\n");
	int i;
	int prev = order[0];
	printf("\t\t-------%d\n",0);
	for(i=0 ; i < size ; i++){
		
		if(prev == order[i]){
			printf("\t\t|  P%d  |\n",prev);
		}
		
		else{
			prev = order[i];
			printf("\t\t-------%d\n",i);
			printf("\t\t|  P%d  |\n",prev);
		}
	}
	printf("\t\t-------%d\n",size);
}
