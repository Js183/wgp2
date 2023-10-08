#ifndef _STACK_H_
#define _STACK_H_
#include <stdbool.h>

typedef char StackElem;

typedef struct
{
	StackElem* pBase;
	StackElem* pTop;
	int size;
} Stack;

struct F_stack{
	double* pTop;
	double* pBase;
	struct F_stack* pLast;//指向父栈
	struct F_stack* pNext;//指向下一个栈的指针
};//定义浮点数栈结构 

typedef enum
{
	OK,ERROR
} Status;//枚举，OK即返回0，表正确；ERROR即返回1，表错误 

Status init_stack(Stack* pStack);//对栈进行初始化
Status init_float_stack(struct F_stack* pStack);//对浮点数栈进行初始化 
void stack_free(Stack *pStack);//释放栈元素的内存
void stack_clear(Stack *pStack);//清空栈 
bool is_empty(Stack* pStack);//判断栈是否为空 
bool is_float_empty(struct F_stack* pStack);//判断浮点数栈是否为空
int stack_length(Stack *pStack);//求栈的长度 
Status stack_get_top(Stack *pStack,StackElem *pElem);//取栈顶元素
Status stack_push(Stack *pStack,StackElem *pElem);//字符入栈 
Status float_stack_push(struct F_stack *pStack,double *pElem);//浮点数入栈 
Status stack_pop(Stack *pStack,StackElem *pElem);//出栈
void float_stack_pop(struct F_stack *pStack,double *pElem);//浮点数出栈
Status stack_traverse(Stack *pStack,Status (*visit)(StackElem*));//遍历栈 

#endif