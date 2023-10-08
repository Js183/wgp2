#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

enum State{
	intState,//整数
	floatState//浮点数
};//枚举整数与浮点数

void transform(char* inPut,char* outPut);//中缀表达式转后缀表达式
int priority(char i);//判断符号优先级 
int judge(char i);//判断当前项为字母数字、符号还是括号

#endif 