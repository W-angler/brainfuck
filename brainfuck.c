#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CODE_LENGTH 4096
#define STACK_FRAME 1024
#define DATA_LENGTH 4096
//code area
char code[CODE_LENGTH];
//stack frame (for nested loop)
char* stack[STACK_FRAME];
//runtime data
char data[DATA_LENGTH];
//code pointer
char* cp=code;
//stack pointer
char** sp=stack;
//data pointer
char* dp=data;
/*
 * function mapping, inspired by a blog.
 * key:instruction character, ASCII
 * value:instruction function, function pointer
 */
typedef void (*INS)();
/*
 * according to ASCII table, ']' is the last character of brainfuck's
 * reserved word and its value is 93, so, to save memory, 94 is enough.
 */
INS ins[94];

/*
 * right shift
 */
void rShift(){
    dp++;
}
/*
 * left shift
 */
void lShift(){
    dp--;
}
/*
 * increase one
 */
void increase(){
    (*dp)++;
}
/*
 * decrease one
 */
void decrease(){
    (*dp)--;
}
/*
 * input
 */
void input(){
    *dp=getchar();
}
/*
 * output
 */
void output(){
    putchar(*dp);
}
/*
 * begin loop
 */
void begin(){
	if(*dp){
		//save loop start position to stack frame
		*sp++=cp-1;
	}
	else{
		//skip to next related ]
		int nested=1;
		for(cp++;*cp&&nested;cp++){
			if(*cp=='[') nested++;
			if(*cp==']') nested--;
		}
	}
}
/*
 *end loop
 */
void end(){
	if(*dp) cp=*(--sp);
}

int main(int argc,char** argv){
	if(argc!=2){
		printf("Usage:%s sourceFile\n",argv[0]);
	}
	else{
		freopen(argv[1], "r", stdin);
		char c;
		while((c = getchar())!= EOF){
			if(strchr("<>+-[].,",c))
				*cp++=c;
			//ignore whitespace and unvalid character
			else if(strchr(" \n\r\t",c))
				continue;
			else
				printf("ignore unvalid character:%c\n",c);
		}
		//reset
		cp=code;
		ins['>']=rShift;
		ins['<']=lShift;
		ins['+']=increase;
		ins['-']=decrease;
		ins[',']=input;
		ins['.']=output;
		ins['[']=begin;
		ins[']']=end;
		while(*cp) ins[*cp++]();
	}
}