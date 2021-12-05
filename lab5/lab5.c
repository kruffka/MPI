#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>

#define N0 54
#define BYTES_PER_PIXEL 3

void LSB_R(char *img, char *msg, int R, int bytes_to_encode) {

    printf("In every byte of every R(%d) pixel lsb is taken\n", R);

    int msg_size = strlen(msg);
    int bit = 0;
    for(int l = N0; l < N0 + bytes_to_encode; l += BYTES_PER_PIXEL*8*R) {
        for(int pixelbyte = 0; pixelbyte < BYTES_PER_PIXEL; pixelbyte++) {
            // printf("%d ", l + pixelbyte*8);
            ((char *)&img[0])[l + pixelbyte*8] &= 0xFFFE | (msg[bit>>3]>>(bit&7))&1;
            bit++;
        }
    }

}

void LSB_M(char *image, char *message) {


}

void Hamming(char *image, char *message) {



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
    FILE *fp = fopen ("imgs/test.bmp", "rb+");

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
        // printf("LSB-M\n");
        // LSB_M(image, N, message);

        break;

    case '3':
        printf("Hamming\n");
        // Hamming(image, N, message);

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