#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
This is a minimal C shell for understanding basic functions
Here is the functionality that will be implemented:

The shell can:

- print prompt
- read command
- parse command
- fork
- child executes program
- parent waits
- repeat forever


Basic process flow

Shell process
[+] User executed a command (fork())
|->>>> Child process

[+] Shell process wait() 
[-] Child process executed (execve()) and killed

[0] back to Shell process
*/

void callfunction(char* argv[]){

    int id = fork();

    if(id == 0){
        //child process
        execvp(argv[0], argv);
        perror("exec failed");
        exit(1);
    } else{
        //parent process
        wait(NULL);
    }
}

int main(){

    while(1){  //infinite loop
        char input[100];
        
        printf(" OwO > "); 
        fgets(input, sizeof(input), stdin);   // this parses the whole line into a string called input
        input[strcspn(input, "\n")] = 0;      // this removes the newline character at the end of input string

        if(strcmp(input, "exit") == 0){       // special functionality of exit command
            break;
        }

        char* command[20]; //array of size 20 of pointer to char datatype
        int i = 0;

        char* token = strtok(input, " ");  // Get input 

        while (token != NULL) {   // convert all inputs to tokens
            command[i++] = token;
            token = strtok(NULL, " "); 
        }
        
        command[i] = NULL;  // Last token given NULL value because that is what callfunction() accepts

        if (strcmp(command[0], "cd") == 0){ 
            int chdir_success;
            if(command[1] == NULL){
                chdir_success = chdir(getenv("HOME"));  
            } else {
                chdir_success = chdir(command[1]);
            }
            if (chdir_success == -1) { 
            printf("No such file or directory\n"); 
            }
            continue;
        }
        callfunction(command);  // finally calling function
    }

    return 0;
}