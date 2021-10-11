#include "../libs/lab.h"

// 0, 1, 2, .., 256
uint8_t alphabet[256] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255};

uint8_t stackOfBooks(uint8_t byte){

    uint8_t c = 0;
    while(alphabet[c] != byte){ c++; }
    
    uint8_t tmp = alphabet[c];
    for(int i = c; i > 0; i--){
        alphabet[i] = alphabet[i - 1];
    }
    alphabet[0] = tmp;

    // for(int i = 0; i < 256; i++){
    //     printf("%d ", alphabet[i]);
    // }
    // printf("\n");
    return c;

}

void main(void){
    char filename[] = "1";
    char books_file[] = "stackOfBooks_f2";

    FILE *file;
    
    file = fopen(filename, "rb"); //doge.png

    if(file == NULL){
        printf("Can't open file\n");
        exit(0);
    }

    FILE *file1;
    file1 = fopen(books_file, "wb"); // rewrite

    int byte;
    uint8_t code = 0;
    unsigned char hex = 0;
    char f2_bin[256];
    uint8_t remainder = 0;
    printf("Reading file\n");
    
    while (byte != EOF) {
        
        if (remainder < 8) {
            byte = getc(file);
            code = stackOfBooks(byte);
            strcpy(f2_bin + remainder, f2(code));
            remainder = strlen(f2_bin);
            // printf("byte = %x code %d f2 %s strlen %d codef2 %s\n", byte, code, f2_bin, strlen(f2_bin), f2(code));
      
        } else { 
            remainder -= 8; // f2_bin > 8 bit

            // 00011010|001 00011| 010010 00| 0100100 0|
            //    11010|001 00011| 010010 00| 0100100 0|
            hex = 0;
            for(int i = 0; i < 8; i++) {
                hex |= (f2_bin[7 - i] & 1) << i;
            }
            strcpy(f2_bin, f2_bin + 8);
            printf("*** hex = %x f2_bin = %s\n", hex, f2_bin);
            fprintf(file1, "%x", hex);
        }
        // printf("######## remainder = %d\n", remainder);
        
        
        // i++;
    }

    // idk 
    remainder -= 15;

    if(remainder > 0) {

        for(int i = remainder; i < 8; i++){
            f2_bin[i] = '0';
        }

        for(int i = 0; i < 8; i++)
                hex |= (f2_bin[7 - i] & 1) << i;
        
        // printf("ch[] = code %d f2 %s codef2 %s remainder %d\n", code, f2_bin, f2(code), remainder);
        // printf("hex = %x f2_bin = %s\n", hex, f2_bin);
  
        fprintf(file1, "%x", hex);
    }

    printf("Done encoding, encoded file: %s\n", books_file);
    
    fclose(file);
    fclose(file1);

    // printf("f2(%d) %s\n", 32, f2(32));
    
    // file = fopen(books_file, "rb");
    // while ((byte = getc(file)) != EOF) {

    //     // code = stackOfBooks(byte);
    //     printf("ch[%d] = %x\n", i, byte);
    //     // fprintf(file1, "%s", f2(code));
    //     i++;
    // }
    //debug
    // for(int i = 0; i < 256; i++){
    //     code = stackOfBooks(i);
    //     printf("ch[%d] = %d code %d\ndone\n", i, i, code);
    // }
    

   

}