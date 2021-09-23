#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *bin(int x){

    // if zero 
    if(x == 0){
        return ""; // not "0"; hack for f1()
    }
        
    uint8_t k = 0;
    // calculate how many zero's before first '1'
    while(!((x << 1) & (1 << 31))){
        k++;
        x = x << 1;
    }

    char *bin_c;
    bin_c = (char *)malloc(32-k); // 32 bits + '\0'

    // write whats left to bin_c
    for(int i = 0; i < 32-k; i++){
        x = x << 1;
        bin_c[i] = x & (1 << 31) ? '1':'0';
    }
    bin_c[31-k] = '\0';

    return bin_c;

}

char *bint(int x){

    // 0, 1 -> ""
    if(x < 2){
        if(x >= 0){
            return "";
        }

        printf("Cant 'bint(%d)' that, value %d < 0\n", x, x);
        exit(1);
    }
    char *bint_c = bin(x);

    int i = 0;
    // shift all chars to left => [i] = [i+1]
    for(i = 0; i < strlen(bint_c) - 1; i++){
        bint_c[i] = bint_c[i + 1];
    }
    bint_c[i] = '\0';
    
    return bint_c;

}

char *f0(int x){

    char *f0_c = (char *)malloc(x + 1);
    
    // len(x) zero's, then 1
    for(int i = 0; i < x; i++){
        f0_c[i] = '0';
    }
    f0_c[x] = '1';
    f0_c[x + 1] = '\0'; 

    return f0_c;

}

char *f1(int x){

    char *bint_c = bint(x);
    char *bin_c = bin(x);
    char *f0_c = f0(strlen(bin_c));

    // f1 = f0(|bin(x)|) + bint(x)
    char *f1_c = (char *)malloc(strlen(bint_c) + strlen(f0_c));
    strcpy(f1_c, f0_c);
    stpcpy(f1_c + strlen(bint_c) + 2, bint_c);

    // free(bint_c);
    // free(bin_c);
    // free(f0_c);

    return f1_c;

}

char *f2(int x){
    
    char *bint_c = bint(x);
    char *bin_c = bin(x);
    char *f1_c = f1(strlen(bin(x)));
    // printf("%d = %s%s\n", x, f1_c, bint_c);

    // f2 = f1(|bin(x)|) + bint(x)
    char *f2_c = (char *)malloc(strlen(f1_c) + strlen(bint_c));
    strcpy(f2_c, f1_c);
    stpcpy(f2_c + strlen(f2_c), bint_c);

    // free(bint_c);
    // free(bin_c);
    // free(f1_c);

    return f2_c;
}

int decode_bint(char *bint_e){

    
    int len = strlen(bint_e);
    int x = 0;
    for(int i = 0; i < len; i++){
        if(bint_e[len - i - 1] == '1')
            x += (1 << i);
    }
    // '1' in the beginning
    return x + (1 << len);
}

int decode_f0(char *encoded){

    int x = 0;
    while(encoded[x] != '1')
        x++;

    return x;

}

int decode_f1(char *encoded){
    
    int x = 0;
    int symbols = strlen(encoded);

    char *f0_d = (char *)malloc(symbols);
    char *bint_d = (char *)malloc(symbols); // 

    // while(symbols){
        // f0
        int k = 0;
        int i = 0;
        while(encoded[k] != '1'){
            k++;
        }

        // cant decode bint(0), so return 0 instead
        if(k == 0){
            return 0;
        }

        for(i = 0; i < k - 1; i++){
            bint_d[i] = encoded[i + k + 1];
        }
        x = decode_bint(bint_d);

        symbols = symbols - k - i;

    // }   
    
    free(f0_d);
    free(bint_d);


    return x;

}


void decode_f2(char *encoded){

    char *f2_d = (char *)malloc(64); // |bin(MAX_INT)| = 40
    char *tmp = (char *)malloc(strlen(encoded));
    strcpy(tmp, encoded);


    int k = 0;
    for(int i = 0; i < strlen(tmp); i++){
        f2_d[i] = tmp[i];
        k++;

        // searching first '1'
        if(tmp[i] == '1'){
            k += k - 2; // num of 000 and 1 - 2 ('0' & '1')

            if(k == 0){ // decode 0
                printf("0 ");
                continue;
            }

            for(int j = i; j < k; j++){
                f2_d[j] = tmp[j];
            }
            f2_d[k] == '\0';

            int bin_mod = decode_f1(f2_d);
            
            for(int m = 0; m < bin_mod; m++){
                f2_d[m] = tmp[m+k];
            }
            f2_d[bin_mod - 1] = '\0';
            printf("%d ", decode_bint(f2_d));
            
            strcpy(tmp, tmp + k + bin_mod - 1);

            k = 0;
            i = -1;
            
        }
    }
    
   // return encoded;
   free(tmp);
   free(f2_d);

}



void main(int argc, char *argv[]){

    char *str = (char *)malloc(64*argc); // |bin(MAX_INT)| = 40
    char *ptr;

    if(argc < 2){
        printf("Give me numbers..\n");
        exit(0);
    }

    printf("Input:\n");
    for(int i = 1; i < argc; i++){
        printf("%d ", atoi(argv[i]));

        ptr = f2(atoi(argv[i]));        
        stpcpy(str + strlen(str), ptr);

    }printf("\n");

    printf("Encoded str = %s\n", str);

    printf("Decoding now...\n");

    decode_f2(str);

    printf("\n");

}