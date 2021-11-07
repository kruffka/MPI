#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

// sort by second to last symbol
int cmp(const void **a, const void **b) {
    
    int len = strlen(*a) - 2;
    // printf("a = %p a = %s b = %p %s\n", *a, *a, b, *b); // +56 +48
    // printf("len = %d\n", len+2);

    // char * const *aa = a;
    // char *const *bb = b;
    char aa = *(const char *)(*(a)+len);
    char bb = *(const char *)(*(b)+len);
    
    // printf("aa = %c bb = %c\n", aa, bb);
    int i = len - 1;
    while(aa == bb && i >= 0){
        aa = *(const char *)(*(a)+i);
        bb = *(const char *)(*(b)+i);
        i--;
    }

    // return aa > bb ? 1 : -1; 
    return aa > bb ? 1 : aa < bb ? -1 : 0;

}

int cmp_int(const void **x1, const void **x2){
    return (*(int *)x1[0] - *(int *)x2[0]);
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
    char **str = (char **)malloc(size*sizeof(char *));
    
    for(i = 0; i < size; i++){
        str[i] = (char *)malloc(size*sizeof(char));
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
    
    // first symb
    int res_code = str[0][0];

    fclose(file);

    printf("[0] %s\n", str[0]);

    for(i = 1; i < size; i++){
        strcpy(str[i], str[i-1] + 1);
        str[i][size - 1] = str[i-1][0];
        // str[i][size] = '\0';

        printf("[%d] %s\n", i, str[i]);
    }

    // for(i = 0; i < size; i++)
    //     printf("[%d] %p\n", i, str[i]);
    // printf("%p\n", str);

    qsort(str, size, sizeof(str[0]), cmp);

    printf("after sort:\n");
    for (i = 0; i < size; i++){
       printf("%s\n", str[i]);

    }
    
    int **arr1 = (int **)malloc(size*sizeof(int *)); // arr 1 and output
    int **arr2 = (int **)malloc(size*sizeof(int *)); // input and arr 2

    for (i = 0; i < size; i++){
        arr1[i] = (int *)malloc(2*sizeof(int));
        arr2[i] = (int *)malloc(2*sizeof(int));
    }

    for(i = 0; i < size; i++){
        // get last symbol from transformed str and set pos to each one
        // input
        arr1[i][0] = str[i][size-1];
        arr1[i][1] = i;
        arr2[i][0] = str[i][size-1];
        arr2[i][1] = i;

    }

    // calculate forward convertion code (first symbol of orig in last column of strings)
    for(i = 0; i < size; i++){
        if(str[i][size-1] == res_code){
            res_code = i;
            break;
        }
    }


    // endo of forward transform
    printf("res (input) => ");
    for(i = 0; i < size; i++){
        printf("%c", arr1[i][0]);
    }
    printf(" %d\n", res_code);


    // inverse convertion
    for(i = 0; i < size; i++){
        printf("%d %c\n", arr1[i][1], arr1[i][0]);
    }
    
    qsort(arr1, size, sizeof(arr1[0]), cmp_int);

    printf("First array (sorted)\n");
    for(i = 0; i < size; i++){
        printf("%c %d\n", arr1[i][0], arr1[i][1]);
    }

    printf("Second array (res_code %d)\n", res_code);
    for(i = 0; i < size; i++){
        arr2[arr1[i][1]][0] = arr1[i][0];   
        arr2[arr1[i][1]][1] = i;
    }

    // output
    for(i = 0; i < size; i++){
        printf("%c %d\n", arr2[i][0], arr2[i][1]);
    }

    i = res_code;
    printf("Output: ");
    for(int j = 0; j < size; j++){
        printf("%c", arr2[i][0]);
        i = arr2[i][1];
    }

    printf("\n");


    for(i = 0; i < size; i++){
        free(str[i]);
        free(arr1[i]);
        free(arr2[i]);
    }

    free(str);
    free(arr1);
    free(arr2);

    // printf("lab3");

}