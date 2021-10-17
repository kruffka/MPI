#include "../libs/lab.h"
// 0 - FIXME
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

    // for(i = 0; i < 256; i++){
    //     printf("%d ", alphabet[i]);
    // }
    // printf("\n");
    return c;

}

void main(void){

    char filename[] = "1"; // doge.png // 1
    char books[] = "stackOfBooks";
    char unzip[] = "res";
    int i;

    FILE *file_r;
    FILE *file_w;
    file_w = fopen(books, "wb"); // rewrite
    file_r = fopen(filename, "rb"); //doge.png

    if(file_r == NULL || file_w == NULL){
        printf("Can't open file_r\n");
        exit(0);
    }

    /* 0100 1101 -> 10110010 перевернуть и делать операции в битовой монжо было б, а не в строке, так как нули теперь значащие будут справа*/

    int byte;
    uint8_t code = 0;
    unsigned char hex = 0;
    char f2_bin[256];
    uint8_t remainder = 0;
    printf("Reading file_r\n");
    
    while (byte != EOF) {
        
        if (remainder < 8) {
            byte = getc(file_r);
            code = stackOfBooks(byte); // zip; code

            strcpy(f2_bin + remainder, f2(code));
            remainder = strlen(f2_bin);
            // printf("byte = %x code %d f2 %s strlen %d codef2 %s\n", byte, code, f2_bin, strlen(f2_bin), f2(code));
      
        } else { 
            remainder -= 8; // f2_bin > 8 bit

            // 00011010|001 00011| 010010 00| 0100100 0|
            //    11010|001 00011| 010010 00| 0100100 0|
            hex = 0;
            for(i = 0; i < 8; i++) {
                hex |= (f2_bin[7 - i] & 1) << i;
            }
            
            printf("*** hex = %x f2_bin = %s rem %s\n", hex, f2_bin, f2_bin + 8);
            strcpy(f2_bin, f2_bin + 8);
            fprintf(file_w, "%c", hex);
        }
        // printf("######## remainder = %d\n", remainder);
        
        
        // i++;
    }

    // idk 
    remainder -= 15;

    if(remainder > 0) {

        for(i = remainder; i < 8; i++){
            f2_bin[i] = '0';
        }

        for(i = 0; i < 8; i++)
            hex |= (f2_bin[7 - i] & 1) << i;
        
        // printf("ch[] = code %d f2 %s codef2 %s remainder %d\n", code, f2_bin, f2(code), remainder);
        printf("hex = %x f2_bin = %s\n", hex, f2_bin);
  
        fprintf(file_w, "%c", hex);
    }


    // file stackOfBooks - zip + f2
    printf("Done encoding, encoded file: %s\n", books);
    
    // printf("str =  %s\n", str);

    // fclose(file_r);
    fclose(file_w);

    // unzip; decode
    file_r = fopen(books, "r"); 
    // file_w = fopen(unzip, "w");

    char *str = "abcdefghijklmnopqrstuvwxyz";
    char str_byte[9] = "01234567\0";
    char str_2byte[16] = "abcdefghijklmnop";
    char rem[16] = "";
    int len = 0;
    int two = 0;
    // int byte_two = 8 << (two&1);

    while ((byte = getc(file_r)) != EOF) {


        int byte_two = 8 << (two&1);

        str = bin(byte);
        len = byte_two - strlen(str);
        for(i = byte_two-8; i < len; i++) {
            str_byte[i] = '0';
        }

        for(; i < byte_two; i++){
            str_byte[i] = str[i - len];
        }
        str_byte[i] = '\0';
        
        printf("str %s byt %s hex %x\n", str, str_byte, byte);

        // if(len < 16){
        // //   strcpy(str_byte + i, str_byte);
            
        // } else {
        //     printf("str_byt %s decode_f2 %d\n", str_byte, decode_f2(&str_byte[0])); 

        // }
        
        
        
        
        if(two&1){

            
            // str_byte[16] = '\0';
            // todo: decode_f2(str) write to variable or file later
            printf("str_byt %s decode_f2 %d\n", str_byte, decode_f2(&str_byte[0])); 
            // while(str_byte[0] == '1'){
            //     printf("str_byt %s decode_f2 %d\n", str_byte, decode_f2(&str_byte[0])); 

            // }


            strcpy(rem, str_byte);

            printf("rem = %s\n", rem);
        }
        
        // }

        two++;
        // if(two == 2) break;

    }
            printf("str_byt %s\n", str_byte);
                
            char da[16] = "0000100100000000";
            // printf("f2 = %d\n", decode_f2(f2(1)));
            printf("df2 = %d\n", decode_f2(&da[0]));

    // while ((byte = getc(file_r)) != EOF) {

    //         str = bin(byte);
    //         len = strlen(str);
            
    //         for(i = len, hex = 0; i >= 0; i--) {
    //             hex |= (str[i - 1] & 1) << (len-i);
    //         }
    //         fprintf(file_w, "%c", hex);
            
    //         printf("str %s hex = %x\n", str, hex);

    // }

    // free(str);
    fclose(file_r);
    // fclose(file_w);

    // file_w = fopen(, "w"); 


    // fclose(file_r);


    // for(i = 0; i < 32; i++)
    //     printf("f2(%d) %s\n", i, f2(i));
    
    // file_r = fopen(books, "rb");
    // while ((byte = getc(file_r)) != EOF) {

    //     // code = stackOfBooks(byte);
    //     printf("ch[%d] = %x\n", i, byte);
    //     // fprintf(file_w, "%s", f2(code));
    //     i++;
    // }
    //debug
    // for(i = 0; i < 256; i++){
    //     code = stackOfBooks(i);
    //     printf("ch[%d] = %d code %d\ndone\n", i, i, code);
    // }
    

   

}