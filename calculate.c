#include "stack.h"
#include "transform.h"
#include "calculate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h> 
void calculate(char* outputFile)
{
	int choice;
	printf("如果您希望将中缀表达式转化为后缀表达式并输出结果，请输入1；\n如果您希望直接输入后缀表达式以获得结果，请输入2：\n");
	scanf ("%d",&choice);
	while (choice != 1 && choice != 2)
    {
        printf("无效的选择，请重新输入1或2：");
        scanf("%d", &choice);
    }
	char* inPut=NULL;
	char outPut[100]={'0'};
	double result; 
		switch (choice){
			case 1:
				printf("输入中缀表达式:\n");
				while(1){
					inPut = readline("");
					if(strcmp(inPut,"quit")==0){
						break;
					}
					add_history(inPut);
					transform(inPut,outPut);
					free(inPut);
					printf("其后缀表达式为%s\n",outPut);//中缀表达式转为后缀表达式
					get_result(outPut,&result);
					//如果有outputFile，将结果写入文件
					if (outputFile!=NULL)
					{
						FILE* file = fopen(outputFile, "a");
						if (file != NULL)
						{
							fprintf(file, "%f\n", result);
							fclose(file);
							printf("结果已写入文件 %s\n", outputFile);
						}
						else
						{
							printf("无法打开文件 %s 以写入结果\n", outputFile);
						}
					}else{
						printf ("result=%f\n",result);
					}
					if(strcmp(inPut,"quit")==0){
						break;
					}
				}
				break;
			case 2:
				printf("输入后缀表达式（为了避免歧义，请在多位数之间添加空格）:\n");
				while(1){
					int c;
					while ((c = getchar()) != '\n' && c != EOF);//清空输入缓冲区中的剩余字符，确保fgets函数能进行 
					fgets(outPut, sizeof(outPut), stdin);
					outPut[strlen(outPut) - 1] = '\0';//将'\n'去除 
					if(strcmp(outPut,"quit")==0){
						break;
					}
					get_result(outPut,&result);
					if (outputFile!=NULL)
					{
						FILE* file = fopen(outputFile, "a");
						if (file != NULL)
						{
							fprintf(file, "%f\n", result);
							fclose(file);
							printf("结果已写入文件 %s\n", outputFile);
						}
						else
						{
							printf("无法打开文件 %s 以写入结果\n", outputFile);
						}
					}else{
						printf ("result=%f\n",result);
					}
				}
				break;
		}
	return;
}

void get_result(char* outPut,double* result)
{
	struct F_stack calculate;//用于计算的栈 
	init_float_stack(&calculate);
	struct F_stack* currentStack=&calculate;//当前栈

	int i;//用于for循环 
	for (i=0;i<strlen(outPut);i++)
	{
		int type=judge(outPut[i]);
		switch(type){
			case 1://读取到数字
				{
					int floatState=0;//标记是否为浮点数
					int token1=0;//用来记录整数部分 
					double token2=0;//用来记录小数部分 
					double pointNumber=10;//用来记录小数的位次 
					
					while (isdigit(outPut[i])||floatState==1){
						if(floatState==0){//整数部分 
							token1=token1*10+outPut[i]-'0';
						}else{//小数部分 
							if(outPut[i]=='.'){
								i++;
								continue;
							}else if(isdigit(outPut[i])){
								token2=token2+(outPut[i]-'0')/pointNumber;
								pointNumber*=10;
							}else{
								floatState=0;
								i--;
							}
						}
						i++;
						if(outPut[i]=='.'){
							floatState=1;
						} 
					}
					i--;
					double number=token1+token2;
					float_stack_push(currentStack,&number);
					break;
				}
			case 2://读取到左括号,进入新栈
				{
					struct F_stack temporary;//用于暂时储存的栈 
					init_float_stack(&temporary);	
					temporary.pLast=currentStack;
					currentStack->pNext=&temporary;
					currentStack=&temporary;
					break;
				}
			case 3://读取到右括号,运算完返回父栈
				{
					double number;
				    if (currentStack->pLast == NULL) { 
			        printf("错误：右括号前没有匹配的左括号\n");
			        return; // 返回非零以表示错误
    				}	
					float_stack_pop(currentStack,&number);
					float_stack_push(currentStack->pLast,&number);
					free(currentStack->pBase);
					free(currentStack->pNext);
					currentStack=currentStack->pLast;
					break;
				}
			case 5://读取到运算符，弹出两个数字并计算
				{
					double pop1,pop2,result;
					if(is_float_empty(currentStack)){
						printf("错误：输入数字不足以进行运算\n");
						return;
					}
					float_stack_pop(currentStack,&pop1);
					if(is_float_empty(currentStack)){
						printf("错误：输入数字不足以进行运算\n");
						return;
					}
					float_stack_pop(currentStack,&pop2);
					switch(outPut[i]){
						case '+':
						result=pop2+pop1;
						break;
						case '-':
						result=pop2-pop1;
						break;
						case '*':
						result=pop2*pop1;
						break;
						case '/':
						if(pop1==0){
							printf("错误：除数不能为零\n");
							return;
						}
						result=pop2/pop1;
						break;
					} 
					float_stack_push(currentStack,&result);
					break;
				}
			case 6://空格
				{
					break;
				}   
		}
	}
	float_stack_pop(currentStack,result);
	free(currentStack->pBase);
	free(currentStack->pNext);
}