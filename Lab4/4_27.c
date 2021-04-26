#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int ans_fb[50];

void *fb(void *num);
int main(int argc, char *argv[]){

	
	pthread_t tid; // thread identifier
	pthread_attr_t attr; // set of thread attributes
	/*setting the default attributes of the thread*/
	pthread_attr_init(&attr);
	/*creating the thread*/
	if(pthread_create(&tid,&attr,fb,argv[1]) != 0){
		printf("Thread was not created\n");
	}
	/*waitng for the thread to exit*/
	pthread_join(tid,NULL);
	
	int numb;
	numb=atoi(argv[1]);
	
	for (int j=0;j<numb;j++){
		printf("%d, ",ans_fb[j]);
	}
	printf("\n");
	return 0;
}

void *fb(void *num){
	int numb;
	numb = atoi(num);
	int i=0;
	for(i;i<numb;i++){
		if(i<=1){
			ans_fb[i]=i;
		}
		else if(i>1){
			ans_fb[i]=ans_fb[i-1]+ans_fb[i-2];
		}
	}
	/*exiting the thread*/
	pthread_exit(0);
}
