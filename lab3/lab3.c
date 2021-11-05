#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

// sort by second to last symbol
int cmp(const void *a, const void *b) {
    
    int len = strlen(a);
    printf("a = %p a = %s b = %p %s\n", a, a, b, b); // +56 +48
    printf("len = %d\n", len);

    char aa = *(char *)(a);
    char bb = *(char *)(b);
    printf("aa = %c bb = %c\n", aa, bb);
    exit(0);

    return aa > bb ? 1 : aa < bb ? -1 : 0;

}


off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}

void main(void){

    char filename[40] = "text.txt";
    int i = 0;

    int size = fsize(filename);
    if (size == -1){
        printf("size of file %s is 0\n", filename);
        exit(0);
    }
    printf("size = %d\n", size);
    
    // up to "size" symbols
    char **str = (char **)malloc(size*40);
    
    for(i = 0; i < size; i++){
        str[i] = (char *)malloc(size);
    }

    FILE *file;
    if ((file = fopen(filename, "r")) == NULL){
        printf("Error reading file");
        exit(0);
    }

    i = 0;
    // read first string from file
    while((str[0][i++] = getc(file)) != EOF);
    str[0][i-1] = '\0';


    fclose(file);


    printf("0 %s\n", str[0]);

    for(i = 1; i < size; i++){
        strcpy(str[i], str[i-1] + 1);
        str[i][size - 1] = str[i-1][0];
        // str[i][size] = '\0';

        printf("[%d] %s\n", i, str[i]);
    }

    for(i = 0; i < size; i++)
        printf("[%d] %p\n", i, str[i]);

    printf("%p\n", str);
    qsort(str, size, sizeof(str[0]), cmp);

    printf("after sort:\n");
    for (i = 0; i < size; i++){
       printf("%s\n", str[i]);

    }


    
    for(i = 0; i < size; i++){
        free(str[i]);
    }

    free(str);

    // printf("lab3");

}