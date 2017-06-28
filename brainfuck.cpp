#include<iostream>
#include<fstream>
#include<vector>
#include<map>
using namespace std;

const int CODE_LENGTH=4096;
const int STACK_FRAME=1024;
const int DATA_LENGTH=4096;

const string reserved="<>+-[].,";
const string whitespace=" \n\r\t";

vector<char> code(CODE_LENGTH,0);
vector<int> stack(STACK_FRAME,0);
vector<char> data(DATA_LENGTH,0);

int cp,sp,dp;

typedef void (*INS)();
map<char,INS> ins;

void rShift(){
    dp++;
}
void lShift(){
    dp--;
}
void increase(){
    data[dp]++;
}
void decrease(){
    data[dp]--;
}
void input(){
	cin>>data[dp];
}
void output(){
	cout<<data[dp];
}
void begin(){
	if(data[dp]){
		stack[sp++]=cp-1;
	}
	else{
		int nested=1;
		for(cp++;code[cp]&&nested;cp++){
			if(code[cp]=='[') nested++;
			if(code[cp]==']') nested--;
		}
	}
}
void end(){
	--sp;
	if(data[dp]){
		cp=stack[sp];
	}
}

int main(int argc,char** argv){
	if(argc!=2){
		printf("Usage:%s sourceFile\n",argv[0]);
	}
	else{
		ifstream in(argv[1]);
		char c;
		while(in>>c,!in.eof()){
			if(reserved.find(c)!=string::npos)
				code[cp++]=c;
			else if(whitespace.find(c)!=string::npos)
				continue;
			else
				cout<<("ignore unvalid character:"+c)<<endl;
		}
		cp=0;
		in.close();
		ins['>']=rShift;
		ins['<']=lShift;
		ins['+']=increase;
		ins['-']=decrease;
		ins[',']=input;
		ins['.']=output;
		ins['[']=begin;
		ins[']']=end;
		while(code[cp]) ins[code[cp++]]();
	}
}
