#include <stdio.h>
#include "stack.h"
#include "transform.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void transform(char* inPut,char* outPut)//将中缀表达式转后缀表达式整理为函数 
{
	Stack myStack;
	init_stack(&myStack);
	int i=0;//用于for循环递增 
	int j=0;//用于字符串递增 
	int type;
	int leftnumber=0;//用于记录左括号次数 
	enum State state = intState;//初始化状态为整数部分
	for (i=0;;i++){
		type = judge(inPut[i]);
		if (type==1){//读取字母 数字时
			//读取数字
			if(isdigit(inPut[i])){
				if(j>0&&judge(outPut[j-1])==1){//只有数字与数字之间才有空格，保证美观
					outPut[j]=' ';
					j++;
				}
				while (isdigit(inPut[i])||state==floatState)//读取到数字时，循环直到不是数字，处理多位数
				{
					outPut[j]=inPut[i]; 
					j++;
					i++;
					if(inPut[i]=='.'){
						state = floatState;//切换状态为浮点数部分				
						}
					if(state==floatState&&inPut[i]!='.'&&judge(inPut[i])!=1){
						state=intState;//重置状态为整数	
					}
				}
				i--;
			}else{//读取字母
				outPut[j]=inPut[i];
				j++;
			} 
		}else if(type==2){//读取左括号时 
			stack_push(&myStack,&inPut[i]);
			leftnumber++;
		}else if(type==3){//读取右括号时 
			if(--leftnumber<0){
			printf("错误：右括号前没有匹配的左括号\n");
			exit(1); //表示程序以错误状态退出
			}
			while(1){
				char elem;
				stack_pop(&myStack,&elem);
				if(elem!='('){
				outPut[j]=elem;
				j++;
				}else break;
			}
		}else if(type==4){//读取'\0'时 
			while(!is_empty(&myStack)){
			char elem;
			stack_pop(&myStack,&elem);
			outPut[j]=elem; 
			j++;
			}
			break;//跳出for循环 
		}else{//读取运算符时 
			while(!is_empty(&myStack)){
				char elem;
				stack_get_top(&myStack,&elem);
				if(elem=='('){
					break;//跳出while 
				}else{
					int Priority1=priority(inPut[i]);
					int Priority2=priority(elem);
					if(Priority2<Priority1) break;//跳出while 
					else {
						char elem2;
						stack_pop(&myStack,&elem2);
						outPut[j]=elem2;
						j++;
					}
				}
			}
			stack_push(&myStack,&inPut[i]);
		}
	}
	outPut[j]='\0';
} 

int priority(char i)//判断符号优先级 
{
	int pri;
	if (i=='+'||i=='-'){
		pri=1;
	}else if (i=='*'||i=='/'){
		pri=2;	
	}
	return pri;
}

int judge(char i) //判断当前项为字母、符号还是括号
{
	int judge;
	if(isalnum(i)){
		judge=1;//字母 数字 
	}else if(i=='('){
		judge=2;//左括号 
	}else if(i==')'){
		judge=3;//右括号 
	}else if(i=='\0'){
		judge=4;//'\0' 
	}else if(i=='+'||i=='-'||i=='/'||i=='*'){
		judge=5;//运算符 
	}else if(i==' '){
		judge=6;//空格 
	}
	return judge;
}

