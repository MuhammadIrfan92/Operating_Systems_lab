#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
typedef struct{
	float x;
	float y;
} point;
int counter;
void *monte_carlo(void *param);
int main(int argc, char *argv[]){
	
	int points = atoi(argv[1]);
	float pie;
	
	pthread_t tid; // thread identifier
	pthread_attr_t attr; // set of thread attributes
	/*setting the default attributes of the thread*/
	pthread_attr_init(&attr);
	/*creating the thread*/
	if(pthread_create(&tid,&attr,monte_carlo,argv[1]) != 0){
		printf("Thread was not created\n");
	}
	/*waitng for the thread to exit*/
	pthread_join(tid,NULL);
	
	
	
	
	pie = (float)(4 * counter)/points;
	
	//printf("total pionts in or onto the cirle are:%d\n",counter);
	printf("pie is:%f\n",pie);
	
	
	
	return 0;
}

void *monte_carlo(void *param){
	int num;
	float distance,a = 1;
	num=atoi(param);
	
	point coord[num];
	
	for (int i=0;i<num;i++){
		coord[i].x=((float)rand()/(float)(RAND_MAX)) * a;
		coord[i].y=((float)rand()/(float)(RAND_MAX)) * a;
	}
	for (int k=0; k<num;k++){
		/*computing distance between point x and y*/
		distance=coord[k].x * coord[k].x + coord[k].y * coord[k].y;
		
		/*if the distance is 1 or less than 1 that means the point lies on or inside circle*/
		if(distance <=1){
			counter++;
		
		}
	}
	
}