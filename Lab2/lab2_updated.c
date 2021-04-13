#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
//#include<readline/readline.h>
//#include<readline/history.h>

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
/*
int takeInput(char* str)
{
	char* buf;

	buf = readline("\n>>> ");
	if (strlen(buf) != 0) {
		add_history(buf);
		strcpy(str, buf);
		return 0;
	} else {
		return 1;
	}
}
*/

int main(){

	FILE *fp;
//	fp = fopen("commands.txt","r");
	int choice;
	pid_t q;
	pid_t ex;
	int exit;
	int none;
	int size;
	printf("\t\t\t\t\t\tWelcome to the shell\n");
	while(exit != 3){
		printf("\n1-Batch Mode\n");
		printf("2-Interactive Mode\n");
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
		char **tokens2;
		int leng;
		printf("Enter your command:");
		scanf("%d",&none);
		fgets(command,150,stdin);
		//add_history(command);
		//takeInput(command);
		printf("Your command is %s\n",command);
		
		leng=strlen(command);
		printf("\n");
		
		
		
		char *check=" && ";
		//*********************************************************************
		if(strstr(command,check) != NULL){
			
			
			char n_command[150],nn_command[150];
			int brek;
			
			for (int i=0;i<strlen(command);i++){
				if(command[i] != '&'){
					n_command[i]=command[i];
				
				}
				else{
				brek=i;
				}
			
			}
			int k=0;
			for (int j =(brek+2);j<strlen(command);j++){
				nn_command[k]=n_command[j];
				k++;
			}
			//printf("s,n_command is %s\n",command);
			//printf("ss,n_command is %s\n",n_command);
			//printf("sss,nn_command is %s\n",nn_command);
			// s-> command, ss-> n_command, sss->nn_command

			
						
			q = fork();
			command[strlen(command)] = '\n';
			for(int i=0;i<strlen(command)-1;i++){
			l[i] = command[i];
			}
			tokens = tokenize(n_command);

			
			
			if(q == 0){
				   if(strcmp(tokens[0],"cd")==0){
				  // printf("waaah");
				   if(tokens[1]!=NULL &&tokens[1]!=".."){
				  // printf("aaaaaa");
				   chdir(tokens[1]);
				   }
				   else if(tokens[1]==NULL){
				   chdir(getenv("HOME"));
				   
				   }
				   else if(tokens[1]==".."){
				   chdir(getenv(".."));
				   }
				   
				   }
			 
			
					if(execvp(tokens[0],tokens) < 0 ){
					printf("\nCould not execute command\n\n");
					}

				}
			else{
				wait(NULL);
				}
				
				//__________________________________________________________
			q = fork();
			command[strlen(command)] = '\n';
			for(int i=0;i<strlen(command)-1;i++){
			l[i] = command[i];
			}
			
			tokens2 = tokenize(nn_command);

			
			if(q == 0){
				   if(strcmp(tokens[0],"cd")==0){
				   //printf("waaah");
				   if(tokens[1]!=NULL &&tokens[1]!=".."){
				   //printf("aaaaaa");
				   chdir(tokens[1]);
				   }
				   else if(tokens[1]==NULL){
				   chdir(getenv("HOME"));
				   
				   }
				   else if(tokens[1]==".."){
				   chdir(getenv(".."));
				   }
				   
				   }
			 
			
					if(execvp(tokens2[0],tokens2) < 0 ){
					printf("\nCould not execute command\n\n");
					}

				}
			else{
				wait(NULL);
				}
				
			
		}
			
		//********************************************************************
		
		else if (command[leng-2]=='&'){
			
					q = fork();
		command[strlen(command)] = '\n';
		for(int i=0;i<strlen(command)-1;i++){
		l[i] = command[i];
		}
		tokens = tokenize(command);

		
		if(q == 0){
	  	       if(strcmp(tokens[0],"cd")==0){
	  	      // printf("waaah");
	  	       if(tokens[1]!=NULL &&tokens[1]!=".."){
	  	       //printf("aaaaaa");
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
				}
			}
		//else{
			//wait(NULL);
			//}
		}
		else{
			
					q = fork();
		command[strlen(command)] = '\n';
		for(int i=0;i<strlen(command)-1;i++){
		l[i] = command[i];
		}
		tokens = tokenize(command);
		//printf("length of tokens is %ld,%ld\n",sizeof(tokens),sizeof(tokens[0]));
		
		//printf("length of tokens is %zu\n",(sizeof(tokens)/sizeof(tokens[0])));
		//printf("%zu\n",sizeof(tokens));
		//printf("%s",tokens);
		
		
		if(q == 0){
	  	       if(strcmp(tokens[0],"cd")==0){
	  	       //printf("waaah");
	  	       if(tokens[1]!=NULL &&tokens[1]!=".."){
	  	       //printf("aaaaaa");
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
				}
			}
		else{
			wait(NULL);
			}
			}
		}
	if(choice == 3){
		ex = getpid();
		kill(ex,SIGKILL);
		
		//printf("pid:%d\n",ex);
		}
	}
//	fclose(fp);
}
