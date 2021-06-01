#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 4 // number of threads

typedef struct Task { 
    void (*taskFunction)(int, int);
    int arg1, arg2;
} Task;

Task taskQueue[256]; // array of Task
int taskCount = 0; // counter variable to hold number of tasks at hand
pthread_t th[THREAD_NUM]; // array of thread identifiers

pthread_mutex_t mutexQueue; // mutex lock queue
pthread_cond_t condQueue; // cond queue

void sum(int a, int b) {
    usleep(50000);
    int sum = a + b;
    printf("Sum of %d and %d is %d\n", a, b, sum);
}

void product(int a, int b) {
    usleep(50000);
    int prod = a * b;
    printf("Product of %d and %d is %d\n", a, b, prod);
}
/*function to execute task which takes pointer to Task(struct) as input*/
void executeTask(Task* task) {
    task->taskFunction(task->arg1, task->arg2);
}
/*function to enqueue task which takes Task(struct) as input*/
void enqueue(Task task){
    taskQueue[taskCount] = task;
    taskCount++;
}

/*function to submit task*/
void submitTask(Task task) {
    pthread_mutex_lock(&mutexQueue); // acquiring mutex lock
    enqueue(task); // enqueuing task
    pthread_mutex_unlock(&mutexQueue); // releasing mutex lock
    pthread_cond_signal(&condQueue); // signaling to indicate task is available
}
/*function to dequeue task*/
void dequeue(){
    int i;
    for (i = 0; i < taskCount - 1; i++) {
        taskQueue[i] = taskQueue[i + 1];
    }
    taskCount--;
}


/*function to start thread*/
void* startThread(void* args) {
    	int i = 0;
	while (i < 25) {
        Task task;
	i++;

        pthread_mutex_lock(&mutexQueue); // acquiring the mutex lock
        while (taskCount == 0) {
            pthread_cond_wait(&condQueue, &mutexQueue); // waiting for the task to be available
	        }

        task = taskQueue[0];
        dequeue();
        pthread_mutex_unlock(&mutexQueue); // releasing the lock
        executeTask(&task); // executing the task
	printf("i is: %d\n",i);
   	}
}
/*function to initialize thread pool*/
void pool_init(){
    int i;
    printf("pool init\n");
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &startThread, NULL) != 0) {
            perror("Failed to create the thread");
        }
    }
}

void pool_shutdown(){
	int i;
	printf("pool shutdown\n");
	for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join the thread");
        }
    }
}

int main(int argc, char* argv[]) {

    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);

    pool_init();

    srand(time(NULL));
    int i;
    for (i = 0; i < 100; i++) {
        Task t = {
            .taskFunction = i % 2 == 0 ? &sum : &product,
            .arg1 = rand() % 100,
            .arg2 = rand() % 100
        };
        submitTask(t);
    }

    pool_shutdown();

    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);
    return 0;
}
