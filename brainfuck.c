#include<stdio.h>

#define STACK_DEPTH 1024

char stack[STACK_DEPTH];

char* ptr=stack;
//right shift
void rShift(){
    ptr++;
}
//left shift
void lShift(){
    ptr--;
}
//increase 1
void increase(){
    (*ptr)++;
}
//decrease 1
void decrease(){
    (*ptr)--;
}
//input
void input(){
    scanf("%c",ptr);
}
//output
void output(){
    putchar(*ptr);
}


