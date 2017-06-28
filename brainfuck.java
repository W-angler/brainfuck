import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Brainfuck{
	interface Instruction{
		void execute();
	}
	private static final int CODE_LENGTH=4096;
	private static final int STACK_FRAME=1024;
	private static final int DATA_LENGTH=4096;
	
	private static final String reserved="<>+-[].,";
	private static final String whitespace=" \n\r\t";
	
	private static final byte[] code=new byte[CODE_LENGTH];
	private static final int[] stack=new int[STACK_FRAME];
	private static final byte[] data=new byte[DATA_LENGTH];
	
	private static int cp,sp,dp;
	private static Map<Byte, Instruction> ins=new HashMap<>();
	private static Scanner in=new Scanner(System.in);
	
	static{
		ins.put((byte)'>',()->dp++);
		ins.put((byte)'<',()->dp--);
		ins.put((byte)'+',()->data[dp]++);
		ins.put((byte)'-',()->data[dp]--);
		ins.put((byte)',',()->data[dp]=in.nextByte());
		ins.put((byte)'.',()->System.out.print((char)data[dp]));
		ins.put((byte)'[',()->{
			if(data[dp]!=0){
				stack[sp++]=cp-1;
			}
			else{
				int nested=1;
				for(cp++;code[cp]!=0&&nested!=0;cp++){
					if(code[cp]=='[') nested++;
					if(code[cp]==']') nested--;
				}
			}
		});
		ins.put((byte)']',()->{
			--sp;
			if(data[dp]!=0){
				cp=stack[sp];
			}
		});
	}
	public static void execute(String file) throws IOException{
		String content=new String(Files.readAllBytes(Paths.get(file)),Charset.forName("UTF-8"));
		for(char c:content.toCharArray()){
			if(reserved.contains(String.valueOf(c)))
				code[cp++]=(byte)c;
			else if(whitespace.contains(String.valueOf(c)))
				continue;
			else
				System.out.println("ignore unvalid character:"+c);
		}
		cp=0;
		while(code[cp]!=0) ins.get(code[cp++]).execute();
	}
	public static void main(String[] args){
		if(args.length!=1){
			System.out.println("Usage:Brainfuck sourceFile");
		}
		else{
			try {
				execute(args[0]);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}