# include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <bits/waitflags.h>
#include <sys/wait.h>

#define BUFFER_SIZE 64
#define DELIM " \t\r\n\a"
char *readline(void)
{
    size_t buffer_size=0;
    char* line=NULL;
    if (getline(&line, &buffer_size, stdin)==-1)    //ead from file/keyboard

    {
       if (feof(stdin))     
        {
            free(line);
            exit(EXIT_SUCCESS);
            
        }

        else 

        {
            free(line);
            perror("error while reading the line from stdin");
            exit(EXIT_FAILURE);
        }

    }

    return line;
}


char** splitline(char* line)

{
    char* token;
    int buff_size=BUFFER_SIZE;
    int pos=0;
    
    char **tokens= malloc(buff_size*sizeof(char*));


    if(tokens==NULL)
    {
        fprintf(stderr,"allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIM);
    while(token!=NULL)
    {   tokens[pos]=token;
        pos++;
        if (pos>buff_size)
        {   buff_size+= BUFFER_SIZE;
            tokens= realloc(tokens,buff_size*sizeof(char*));

        }
        if(tokens==NULL)
        {
        fprintf(stderr,"allocation error");
        exit(EXIT_FAILURE);
        }
       
        token =strtok(NULL, DELIM);
    }
    tokens[pos]=NULL;
    
return tokens;
}

int launch(char **args){
    pid_t pid, wpid;
    int status;
     pid=fork();   //process ID

     if (pid==0){       
        if (execvp(args[0],args)==-1)

        {
            perror("error in new_process:child process");
        }
        exit(EXIT_FAILURE);  
     }
    else if (pid<0){
        perror("error in new_process: forking");
        }

    else
    {  
        do{
            waitpid(pid, &status, WUNTRACED);
        }
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int my_cd(char **args);
int my_help(char **args);
int my_exit(char **args);


char* builtin[]={
    "cd",
    "help",
    "exit"
};

int (*builtins[]) (char**)={
    &my_cd,
    &my_help,
    &my_exit
 
};
int num_builtins() {
  return sizeof(builtin) / sizeof(char *);
}

int my_cd(char **args){
    if (args[1]==NULL){
        fprintf(stderr, "expected argument to \"cd\"\n");
    }
    else
	{
		if (chdir(args[1]) != 0)
		{
			perror("error in my_cd.c: changing dir\n");
		}
	}

    return 1;
    }

int my_exit(char **args){
    return 0;
}

int my_help(char **args){
    int i;
    printf("\n...help my_shell");
    printf("Type a command and its arguments, then hit enter\n");
    printf("Built-in commands:\n");

    for (i=0; i<num_builtins(); i++){
        printf("%s\n",builtin[i]);
    }
     printf("Use the man command for information on other programs.\n");
  return 1;
}

int execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < num_builtins(); i++) {
    if (strcmp(args[0], builtin[i]) == 0) {
      return (*builtins[i])(args);
    }
  }

  return launch(args);
}



void loop(){
char *read;
char **split; 
int status;
 
 do{
printf(">");
read = readline();
split=splitline (read);
status=execute(split);
free(read);
free(split);
 }while(status);



}
int main(int argc, char **argv){

/*char *read;
char **split; 
char **args;


read = readline();
printf ("%s", read);
split=splitline (read);
printf("%s\n",split[0]);

free(read);
free(split);*/

loop();
return(EXIT_SUCCESS);

}




