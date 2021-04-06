#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

char **tokenize(char *line)
{
	char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	int i, tokenIndex = 0, tokenNo = 0;

	for(i = 0; i < strlen(line); i++){
		char readChar = line[i];
		if(readChar == ' ' || readChar == '\n' || readChar == '\t'){
		token[tokenIndex] = '\0';
		if(tokenIndex != 0){
			tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE * sizeof(char));
			strcpy(tokens[tokenNo++],token);
			tokenIndex = 0;
			}
		}
		else{
		token[tokenIndex++] = readChar;
		}
	}
	free(token);
	tokens[tokenNo] = NULL;
	return tokens;
}
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}


int main(){

	FILE *fp;
//	fp = fopen("commands.txt","r");
	int choice;
	pid_t q;
	int exit;
	int none;
	int size;
	printf("\t\t\t\t\t\tWelcome to the shell\n");
	while(exit != 3){
		printf("\n1-Batch Mode\n");
		printf("2-Type Command\n");
		printf("3-Exit shell\n");

		printf("Enter your choice\n");
		scanf("%d",&choice);
	if(choice == 1){ 	//	Batch Mode
	fp = fopen("commands.txt","r");
	printf("\n");
	while(!feof(fp)){
		char l[150] = "";
		char line[150] = "";
		char **tokens;
		fgets(line,150,fp);
		if(strlen(line) > 0){
			printf("Command is %s\n",line);
			line[strlen(line)] = '\n';
			tokens = tokenize(line);
			q = fork();
			if(q == 0){
				if(execvp(tokens[0],tokens) < 0){
					printf("\nCould not execute command\n\n");
					};
				}
			else{
				wait(NULL);
		//		printf("In parent\n");
				}
			}
		}
	fclose(fp);
	}
	if(choice == 2){	//	Interactive Mode
		char command[150];
		char l[150];
		char **tokens;
		printf("Enter your command:");
		scanf("%d",&none);
		fgets(command,150,stdin);
		printf("Your command is %s\n",command);
		q = fork();
		command[strlen(command)] = '\n';
		for(int i=0;i<strlen(command)-1;i++){
		l[i] = command[i];
		}
		tokens = tokenize(command);
		if(q == 0){
	  	       if(strcmp(tokens[0],"cd")==0){
	  	       printf("waaah");
	  	       if(tokens[1]!=NULL &&tokens[1]!=".."){
	  	       printf("aaaaaa");
	  	       chdir(tokens[1]);
	  	       }
	  	       else if(tokens[1]==NULL){
	  	       chdir(getenv("HOME"));
	  	       
	  	       }
	  	       else if(tokens[1]==".."){
	  	       chdir(getenv(".."));
	  	       }
	  	       
	  	       }
	  	 
		
			else if(execvp(tokens[0],tokens) < 0){
				printf("\nCould not execute command\n\n");
				};
			}
		else{
			wait(NULL);
			}
		}
	if(choice == 3){
		exit = 3;
		printf("\t\t\t\t\t\tExiting shell\n");
		}
	}
//	fclose(fp);
}
