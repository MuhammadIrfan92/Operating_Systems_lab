#include<stdio.h>

void min(int array[], int* minimum, int* ind,int size);
void gant(int order[],int size);

int main(){
	int i=0;
	int num = 4;//number of processes
	int process[num] = {1,2,3,4};
	int burst[num]   = {53,17,68,24};
	
	int queue[3] = {1,2,3};
	int queue1[num];
	int queue2[num];
	int queue3[num];
	int cur[num];
	int priority[3] = {1,2,3};
	int size = sizeof(process)/sizeof(process[0]);
	int burst2[num];
	for(i=0;i<num;i++){
		burst2[i] = burst[i];
	}
	
	printf("\t\t--------------------------------------------------\n");
	printf("\t\t| \t  Process \t | \t Burst \t\t |\n");
	printf("\t\t--------------------------------------------------\n");
	
	for(i=0; i < num; i++){
	
	printf("\t\t| \t  P %d \t\t | \t %d \t\t |\n",process[i],burst[i]);
	printf("\t\t--------------------------------------------------\n");
	}

	for(i=0;i<num;i++){
		queue1[i] = i;
		queue2[i] = -1;
		queue3[i] = -1;
	}
	int q,cur_q;
	int q1 = 10;
	int q2 = 20;
	int q3 = 30;
	int j,k;
	int time = 0;
	int ins1 = 0;
	int ins2 = 0;
	int minimum,ind;
	int p,sol,count3=0;
	int end_time[num];
	int order[100];
	int o=0;
	//Solution
	for(i=0;i<3;i++){
	
	if(i <2){
	min(priority,&minimum,&ind,3);
	priority[ind] = -1;
	q = queue[ind];
	if(q == 1){
		for(k=0;k<num;k++){
			cur[k] = queue1[k];
			cur_q = q1;
		}
	}
	else if(q == 2){
		for(k=0;k<num;k++){
			cur[k] = queue2[k];
			cur_q = q2;
		}
	}
	
	for(j=0;j<num;j++){
		if(burst[cur[j]] > cur_q){
			burst[cur[j]] -= cur_q;
			time += cur_q;
			order[o++] = cur[j];
			if(q == 1){
				queue2[ins1++] = cur[j];
			}
			else if(q == 2){
				queue3[ins2++] = cur[j];
			}
		}
		else if(burst[cur[j]] == cur_q){
				burst[cur[j]] -= cur_q;
				time += cur_q;
				end_time[cur[j]] = time;
				order[o++] = cur[j];
		}
		else if(burst[cur[j]] > 0){
			time += burst[cur[j]];
			burst[cur[j]] = 0;
			end_time[cur[j]] = time;
			order[o++] = cur[j];
			}	
		}	
	}
	else{
		for( i = 0 ; i < 2 ; i++){
			if(burst[queue3[0]] > q3){
				burst[queue3[0]] -= q3;
				time += q3;
				order[o++] = queue3[0];
			}
			else if(burst[queue3[0]] == q3){
				burst[queue3[0]] -= q3;
				time += q3;
				end_time[queue3[0]] = time;
				order[o++] = queue3[0];
				queue[0] = -1;
			}
			else{
				time += burst[queue3[0]];
				burst[queue3[0]] = 0;
				end_time[queue3[0]] = time;
				order[o++] = queue3[0];
				queue3[0] = -1;
			}
			for(j=0;j<ins2;j++){
				queue3[j] = queue3[j+1];
			}
			for(j=0;j<ins2;j++){
				if(queue3[j] != -1){
					count3 ++;
				}
			}
			if(count3 == 1){
				time += burst[queue3[0]];
				burst[queue3[0]] = 0;
			}
		}}
	}
	int turnaround[num];
	int waiting[num];
	float turn=0;
	float wait=0;
	for(i=0;i<num;i++){
		turnaround[i] = end_time[i];
		turn += turnaround[i];
		waiting[i] = turnaround[i] - burst2[i];
		wait += waiting[i];
	}
	printf("Avg Turn Around time is %0.2f\n",turn/num);
	printf("Avg Waiting time is %0.2f\n",wait/num);
}

void min(int array[], int* minimum, int* ind, int size){
	int i;
	*minimum = 100;
	*ind = 0;
	for(i=0;i<size;i++){
		if((array[i] < *minimum) && array[i] != -1){
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
