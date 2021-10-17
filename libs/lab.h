#ifndef LAB_H
#define LAB_H


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


char *bin(int x);
char *bint(int x);
char *f0(int x);
char *f1(int x);
char *f2(int x);
int decode_bint(char *bint_e);
int decode_f0(char *encoded);
int decode_f1(char *encoded);
int decode_f2(char *encoded);


#endif // LAB_H