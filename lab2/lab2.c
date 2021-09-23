#include <stdio.h>
#include <stdlib.h>


void main(void){

    FILE *file;
    
    file = fopen("doge.png", "rb");

    if(file == NULL){
        printf("Cant open file\n");
        exit(0);
    }

    int ch;
    int i = 0;
    while ((ch = getc(file)) != EOF) {

        printf("ch[%d] = %x\n", i, ch);
        i++;
    }
    

    
}