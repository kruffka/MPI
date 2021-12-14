/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ASCII_SIZE 256

int main(void)
{
    
    char str[1000] = "aaaaaabcbabcabcaaaabbbbcacccccccccabacacabacbcbcbabaababcbcbcbcbabaababcbcbcbabaababcbcbcbabaababcacbabcbcabcabcbabcababbcbbbcababcbabcabcabcbabcabbacbcabbaaaabababbbcbcbbbabbcbcbbbbcababcbabcabcabcbbbcababcbabcabcabcbabcaabcababbcbababcbacbcbbcbcbcbcbcbbacbcabbaaaabababbbcbcbbbabbcbcbbbbcababcbabcabcabcbabcabcacabbbcababcbabcabcabcbabcabbbcababcbabcabcabcbabcabbbcababcbabcabcabcbabcabbbcababcbabcabcabcbabca";
    
    // printf("str len = %d\n", strlen(str));

    int n = 2; // Число символов
    int big = pow(ASCII_SIZE, n);

    int16_t *map = (int16_t *)malloc(sizeof(int16_t)*big); // i.e. 65536 для двух (256*256)
    memset(&map[0], 0, big);

    int str_s = strlen(str);
    
    int idx = 0, i = 0;
    while(str[i + n - 1]) { // != '\0'

        // map['b' * 'a'] работало для двух сторон, ab и ba, пришлось немного переделать:
        // map[(str[i] - 1)*255 + str[i + 1]]++; // для двух
        // map[x*9 + y*3 + z*1;]++; // для трех символов, максимум bi

        // Для n символов
        for(int m = 0; m < n; m++) {
            idx += pow(ASCII_SIZE, n - m - 1)*str[i + m];

        }
        // map[(str[i] - 2)*255 + (str[i + 1] - 1)*255 + str[i + 2]]++;
        // printf("iii %d idx %d\n", i, idx);

        map[idx]++;
        idx = 0;
        i++;
        
    }
    
    // printf("%d\n", map[('a')*9 + ('a')*3 + 'b'*1]);


    char abc[9] = {'a', 'b', 'c'};
    int a_size = 3;
    int bit = 0;
    // for(int i = 0; i < a_size; i++) {
    //     for(int j = 0; j < a_size; j++) {
    //         printf("%.9f  %c %c\n", 1./map[abc[i]*ASCII_SIZE + abc[j]*1]/str_s, abc[(bit >> 2) & 0x3], abc[bit & 0x3]); // , abc[i]*ASCII_SIZE + abc[j]
    //         bit++;
    //     }
    // }
    
    int res = 0;
    int j = n - 1;
    i = 0;
    char strOut[n+1];
    int nn = pow(a_size, n);

    while(res < nn) {
        for(j = n - 1; j >= 0; j--) {
            if (((bit>>(2*j))&0x3) >= a_size){
                break;
            }
            strOut[n-1-j] = abc[((bit>>(2*j))&0x3)];
        }  
        if (j == -1){
            strOut[n] = '\0';
            for(j = 0; j < n; j++) {
                idx += strOut[j]*pow(ASCII_SIZE, n - j - 1);
            }
            printf("%s %.9f\n", strOut, 1.0 / map[idx] / str_s);
            idx = 0;
            res++;
        }
        bit++;
    }


    free(map);
    
    return 0;
}
