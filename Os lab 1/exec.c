#include  <stdio.h>
#include  <sys/types.h>
void  parse(char *line, char **argv)
{
     while (*line != '\0') {  
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0'; 
          *argv++ = line;       
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             
     }
     *argv = '\0';                
}
     
void  execute(char **argv)
{
     pid_t  pid;
     int    status;
     
     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(*argv, argv) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}
     
void  main(void)
{
     char  line[1024];      
     char  *argv[64];  
     while (1) {  
          printf("Shell -> ");   
          gets(line);   
          printf("\n");
          parse(line, argv);
          if (strcmp(argv[0], "exit") == 0) 
               exit(0);  
          execute(argv);
     }
}