#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
	FILE *fpointer;
	fpointer = fopen("commands.txt","r");
	char line[150];

	int size;
	int i=0;
	pid_t q; // to handle process ids
	int u=0;
	while(!feof(fpointer)){ // feof tests the end of the file indicator for the given stream
	i++;
	char l[150] = "0";
	fgets(line,150,fpointer);
//	puts(line);
	size = strlen(line);
//	printf("\nsize is %d\n",size);
	printf("Command is %s\n",line);
	for(int j=0;j<size-1;j++){
		l[j] = line[j];
		}
//	write(1,line,s);
//	printf("\nline is %s\n",line);
//	printf("\nl is %s\n",l);

	q = fork();

	if(q==0){
//		printf("\nIn child\n");
		execlp(l,l,NULL);
		printf("\n");
		}
	else{
		wait(NULL);
//		printf("\nIn parent\n");
		}
	}
//	printf("i is %d\n",i);
	fclose(fpointer);
	return 0;
}