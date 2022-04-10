#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>

#define N0 54
#define BYTES_PER_PIXEL 3

int H[4][15] = {
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}    
};

void LSB_R(char *img, char *msg, int R, int bytes_to_encode) {

    printf("In every byte of every R(%d) pixel lsb is taken\n", R);

    int bit = 0;
    for(int l = N0; l < N0 + bytes_to_encode; l += BYTES_PER_PIXEL*8*R) {
        for(int pixelbyte = 0; pixelbyte < BYTES_PER_PIXEL; pixelbyte++) {
            // printf("%d ", l + pixelbyte*8);
            printf("%d ", ((char *)&img[0])[l + pixelbyte*8] & 1);
            ((char *)&img[0])[l + pixelbyte*8] &= 0xFFFE | (msg[bit>>3]>>(bit&7))&1;
            printf("%d\n", ((char *)&img[0])[l + pixelbyte*8] & 1);
        
            bit++;
        }
    }

}

void LSB_M(char *img, char *msg, int R, int bytes_to_encode){
    
    printf("In every byte of every R(%d) pixel lsb is taken\n", R);

    int bit = 0;
    for(int l = N0; l < N0 + bytes_to_encode; l += BYTES_PER_PIXEL*8*R) {
        for(int pixelbyte = 0; pixelbyte < BYTES_PER_PIXEL; pixelbyte++) {

            if(((char *)&img[0])[l + pixelbyte*8] == 0 || ((char *)&img[0])[l + pixelbyte*8] == -1) {
                // printf("%d 0000 or 255\n", bit);
                ((char *)&img[0])[l + pixelbyte*8] = ((char *)&img[0])[l + pixelbyte*8] & 0xFFFE | (msg[bit>>3]>>(bit&7))&1;

                bit++;
                continue;
            }

            if(((((char *)&img[0])[l + pixelbyte*8] & 1) - (msg[bit>>3]>>(bit&7))&1) == 0){
                // printf("%d equal\n", bit);
                // do nothing

            } else {
                // printf("%d not equal\n", bit);

                // xor
                ((char *)&img[0])[l + pixelbyte*8] = (((char *)&img[0])[l + pixelbyte*8] & 0xFFFE) ^ 1;


            }
            
            bit++;
        }
    }


}

void Hamming(char *img, char *msg, int R) {

    int msg_ptr = 0, i;
    int msg_size = strlen(msg)*8;
    int H_ct[4] = {0};
    int s[4] = {0};

    for(int byte = N0; byte < N0 + msg_size; byte++){
        
        // 4*2 bits in 1 byte
        for(int msg_half = 0; msg_half < 2; msg_half++){
            for(int b = 0; b < 15; b++){
                H_ct[0] |= H[0][b] & (img[b]&1);
                H_ct[1] |= H[1][b] & (img[b]&1);
                H_ct[2] |= H[2][b] & (img[b]&1);
                H_ct[3] |= H[3][b] & (img[b]&1);
                // H_ct[l/4] = H_ct[l/4] + 
            }
            
        // printf("%d\n%d\n%d\n%d\n", H_ct[0], H_ct[1], H_ct[2], H_ct[3]);

        i = 0;
        for(int m = 0; m < 4; m++) {
            s[m] = H_ct[m] ^ ((((char *)&msg[0])[byte] >> msg_ptr) & 1);
            // printf("%d ", (((char *)&msg[0])[msg_half] >> msg_ptr) & 1);
            msg_ptr++;
            i += s[m]*pow(2, m);
        }

        // printf("%d\n%d\n%d\n%d\n%d", s[0], s[1], s[2], s[3], i);

        i += byte;
        // printf("%d\n", img[N0 + i]);
        img[N0 + i] = img[N0 + i] & 0xFFFE | (~img[N0 + i])&1;
        // printf("%d\n", img[N0 + i]);
        }

        msg_ptr = 0;
        for(int j = 0; j < 4; j++){
            H_ct[j] = 0;
            s[j] = 0;

        }

        // printf("%d: %d\n", byte, img[i]&1);
        
        
    }


}



void main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Not enough arguments, 1 - LSB-R; 2 - LSB-M; 3 - Hamming\n");
        exit(0);
    }

    char *image;
    // size of file and code rate 
    int N;
    float rate = 0.25;
    char message[] = "message";
    
    // 24 bits one pixel = 3 bytes rgb, 1 lsb per byte
    // every R pixel 3 bytes of data
    int R = 1/rate;
    
    // in bits
    int msg_size = strlen(message)*8;

    struct stat st;
    FILE *fp = fopen ("imgs/PU24-4.bmp", "rb+");

    if(fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fstat (fileno(fp), &st);
    N = st.st_size;
    // printf("file size = %d bytes\n", N);

    // +24
    int bytes_to_encode = ceil(msg_size*8.0/(BYTES_PER_PIXEL*8))*BYTES_PER_PIXEL*8*R - 24*(R-1);
    // printf("bytes_to_encode %d\n", bytes_to_encode + N0);


    if(N0 + bytes_to_encode > N) {
        
        printf("Message is too loong, not enough bytes to lsb, N0(%d) + bytes to decode (%d) > size of file (%d)\n", N0, bytes_to_encode, N);
        exit(1);
    }    

    image = (char *)malloc(sizeof(char)*N);
    fread(image, 1, N, fp);

    switch (argv[1][0])
    {
    case '1':

        printf("LSB-R\n");
        LSB_R(image, message, R, bytes_to_encode);

        break;

    case '2':
        printf("LSB-M\n");
        LSB_M(image, message, R, bytes_to_encode);

        break;

    case '3':
        printf("Hamming\n");
        Hamming(image, message, R);

        break;
    
    default:
        printf("1 - LSB-R; 2 - LSB-M; 3 - Hamming\n");

        break;
    }


    // байты изображения идут с image[54] по image[N-1]
    // в них можно внедрять скрытые данные, изменяя младшие биты
    rewind(fp);

    fwrite(image, 1, N, fp);
    fclose(fp);

    free(image);


    // getchar();
}