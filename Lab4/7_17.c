#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define THREADS 5

typedef struct{
	float x;
	float y;
} point;

int counter; // for counting number of points inside or onto the circle


pthread_mutex_t mutex;

void *monte_carlo(void *param);

int main(int argc, char *argv[]){
	
	int points = atoi(argv[1]);
	float pie;
	
	
	if(pthread_mutex_init(&mutex,NULL) != 0){
		printf("mutex lock initialization failed\n");
	}
	
	pthread_t tid[THREADS]; // thread identifiers
	pthread_attr_t attr; // set of thread attributes
	
	
	/*setting the default attributes of the thread*/
	pthread_attr_init(&attr);
	/*creating the thread*/
	
	for(int i=0; i<THREADS;i++ ){
		if(pthread_create(&tid[i],&attr,monte_carlo,argv[1]) != 0){
			printf("Thread was not created\n");
		}
		
	}
	
	for(int i=0; i<THREADS;i++ ){
		pthread_join(tid[i],NULL);
		
	}
	if(pthread_mutex_destroy(&mutex) != 0){
		printf("Mutex could not be destroyed\n");
	}
	counter = counter / THREADS;
	
	pie = (float)(4 * counter)/points;
	
	//printf("total pionts in or onto the cirle are:%d\n",counter);
	printf("pie is:%f\n",pie);
	
	return 0;
}

void *monte_carlo(void *param){
	pthread_mutex_lock(&mutex);
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
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
	
}
