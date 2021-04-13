#include<stdio.h>

void min(int array[], int* minimum, int* ind,int size);
void gant(int order[],int size);

int main(){
	int i=0;
	int num = 5;//number of processes
	int process[num] = {1,2,3,4,5};
	int burst[num]   = {4,5,8,7,3};
	int priority[num] = {3,2,2,1,3};
	int size = sizeof(process)/sizeof(process[0]);
	int burst2[num];
	for(i=0;i<num;i++){
		burst2[i] = burst[i];
	}
	
	printf("\t\t------------------------------------------------------------------\n");
	printf("\t\t| \t  Process \t | \t Burst \t\t |   Priority    |\n");
	printf("\t\t------------------------------------------------------------------\n");
	
	for(i=0; i < num; i++){
	
	printf("\t\t| \t  P %d \t\t | \t %d \t\t | \t %d \t |\n",process[i],burst[i],priority[i]);
	printf("\t\t------------------------------------------------------------------\n");
	}
	

	//Solution
	int quantum = 0;//2
	int time=0;
	int j,k;
	int start_time[100];
	int end_time[100];
	int st=0;
	int et=0;
	int ready[size] = {-1,-1,-1,-1,-1};
	int c = 0;
	int temp;
	int complete = 0;
	int count=0;
	int count2=0;
	int order[100] = {-1};
	int o=0;
	int d=0;
	int dup[size];
	int size2,element;

	for(c=0;c<size;c++){
	d = 0;
	int minimum,ind;
	min(priority,&minimum,&ind,num);
	
	//FOR duplicates
	for(i=0;i<size;i++){
		if(minimum == priority[i]){
			dup[d++] = i;
			size2++;
		}}
	
	if(size2==1){
		start_time[st++] = time;
		for(i=0;i<burst[ind];i++){
			order[o++] = ind+1;
		}
		time += burst[ind];
		burst[ind] = 0;
		end_time[st++] = time;
		priority[ind] = -1;
	}
	else{
			i=0;
			int total_burst=0;
			for(i=0;i<size2;i++){
				total_burst += burst[dup[i]];
				priority[dup[i]] = -1;
			}
			for(i = 0;i < total_burst ; i++){
				order[o++] = dup[0]+1;
				burst[dup[0]]--;
				time++;
				quantum++;
				if(burst[dup[0]] == 0 && (quantum == 2 || quantum == 1) ){
					quantum = 0;
					for(j=0;j<size2;j++){
						if(dup[j+1] != 1){
						dup[j] = dup[j+1];
					}}
					dup[size2-1] = -1;
					for(j=0;j<size2;j++){
					}}
				if(quantum == 2 && burst[dup[0]] != 0){
					quantum = 0;
					element = dup[0];
					for(j=0;j<size2;j++){
						if(dup[j+1] != -1){
						dup[j] = dup[j+1];	
					}}
					dup[size2-1] = element;
					for(j=0;j<size2;j++){
					}}
				}
			}
	size2 = 0;
	}
	//GANT  CHART
	gant(order,time);
}

void min(int array[], int* minimum, int* ind, int size){
	int i;
	*minimum = array[0];
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
