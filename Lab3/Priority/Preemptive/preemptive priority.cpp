#include<stdio.h>

void gant(int order[],int time);

int main(){
	int i;
	int num = 5;//number of processes
	int process[num] = {1,2,3,4,5};
	int arrival[num] = {0,5,12,2,9};
	int burst[num]   = {11,28,2,10,16};
	int priority[num] = {2,0,3,1,4};		//	0 is highest priority
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
	int j,k,current,count=0;
	int start_time[size];
	int end_time[size];
	int order[100];
	int done = 0;
	int pr = 1000;
	int lp = -1;
	int lc = -1;
	int ex[size]={0};
	i = 0;
	int flag=-1;
	int t=0;
	
	while(done != 1){
		for(j=0;j<size;j++){
			if(time >= arrival[j]){
				if(priority[j] < pr && burst[j] > 0 && priority[j] != -1){
					pr = priority[j];	
					current = j;			
				}}}
		if(lp != pr && burst[lc] > 0){
			ex[lc] = t;
			t = 0;
		}
		lc = current;
		lp = pr;
		pr = 1000;
		if(flag != current){
			start_time[current] = time;
			flag = current;	
		}
		burst[current]--;
		order[i] = current+1;
		time++;
		t++;
		if(burst[current] == 0){
			end_time[current] = time;
			priority[current] = -1;
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
		i++;
	}
	gant(order,time);
	
	int waiting_time[size];
	float avg_wait = 0;
	for(i=0;i<size;i++){
		waiting_time[i] = start_time[i] - ex[i] - arrival[i];
		avg_wait += waiting_time[i];
	}
	printf("Avg Waiting time is %0.2f\n",avg_wait/size);
	
	int prev[size];
	int pr2=0;
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
						response += (i - arrival[order[i]-1]);
						prev[pr2++] = order[i];
					}
					else{
						c = 0;
					}
				}}
		else{
			prev[pr2++] = order[0];
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
