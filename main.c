#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define  READ 0
#define WRITE 1
int main(){
  int fds1[2],fds2[2];
  pipe(fds1);
  pipe(fds2);
  char text[1000];
  printf("This programs takes in text from stdin and the child function reverses its order\n");
  int f = fork();
  while(1){
    if (f == 0){
      close(fds1[READ]);
      close(fds2[WRITE]);
      printf("Enter Text: ");
      fgets(text,1000,stdin);
      char * n = strchr(text,'\n');
      *n = 0;
      write(fds1[WRITE], text,sizeof(text));
      read(fds2[READ],text,sizeof(text));
      printf("String Out: %s\n",text);
    }
    else{
      close(fds1[WRITE]);
      close(fds2[READ]);
      read(fds1[READ],text,sizeof(text));
      int i,hold,length;
      length = strlen(text);
      for (i = 0; i < length/2;i++){
       hold = text[i];
       text[i] = text[length - i - 1];
       text[length - i - 1] = hold;
      }

      write(fds2[WRITE],text,sizeof(text));

    }
  }
}
