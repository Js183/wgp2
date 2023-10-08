#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

#define maxSize 100 //最大容量暂设为100 

Status init_stack(Stack* pStack)//对栈进行初始化 
{
	pStack->pBase=(StackElem*)malloc(maxSize*sizeof(StackElem));
	if (pStack->pBase==NULL)
	{
		return ERROR;
	}
	pStack->pTop=pStack->pBase;
	pStack->size=maxSize;
	return OK;
}

Status init_float_stack(struct F_stack* pStack)//对浮点数栈进行初始化 
{
	pStack->pBase=(double*)malloc(maxSize*sizeof(double));
	if (pStack->pBase==NULL)
	{
		return ERROR;
	}
	pStack->pTop=pStack->pBase;
	pStack->pNext=(struct F_stack*)malloc (sizeof(struct F_stack));
	pStack->pLast=(struct F_stack*)malloc (sizeof(struct F_stack));
	pStack->pNext=NULL;
	pStack->pLast=NULL;
	return OK;
}

void stack_free(Stack *pStack)//释放栈元素的内存
{
	free (pStack->pBase);
	pStack->pBase=NULL;
	pStack->pTop=NULL; 
}

void stack_clear(Stack *pStack)//清空栈
{
	pStack->pTop=pStack->pBase;
}

bool is_empty(Stack* pStack)//判断栈是否为空
{
	if(pStack->pBase==pStack->pTop){
		return true;
	}else{
		return false;
	}
}

bool is_float_empty(struct F_stack* pStack)//判断浮点数栈是否为空
{
	if(pStack->pBase==pStack->pTop){
		return true;
	}else{
		return false;
	}
}

int stack_length(Stack *pStack)//求栈的长度
{
	return pStack->pTop - pStack->pBase;
}

Status stack_get_top(Stack *pStack,StackElem *pElem)//取栈顶元素
{
	if(is_empty(pStack)){
		return ERROR;
	}
	*pElem=*(pStack->pTop-1);
	return OK;
}

Status stack_push(Stack *pStack,StackElem *pElem)//字符入栈
{
	//如果内存不够，尝试增加内存，若无法增加则返回ERROR 
	if(pStack->pTop - pStack->pBase==pStack->size) {
		int newMaxSize=maxSize+10;
		StackElem* newpBase=(StackElem*)realloc(pStack->pBase,newMaxSize*sizeof(StackElem));
		if (newpBase==NULL){
			return ERROR;
		}
		pStack->pBase=newpBase;
		pStack->pTop=pStack->pBase+pStack->size;
		pStack->size=newMaxSize;
	}
	*(pStack->pTop)=*pElem;
	pStack->pTop++;
	return OK;
}

Status float_stack_push(struct F_stack *pStack,double *pElem)//浮点数入栈 
{
		*(pStack->pTop)=*pElem;
		pStack->pTop++;
		return OK;
}

Status stack_pop(Stack *pStack,StackElem *pElem)//出栈
{
	if(is_empty(pStack)){
		return ERROR;
	}
	*pElem=*(pStack->pTop-1);
	pStack->pTop--;
	return OK;
} 

void float_stack_pop(struct F_stack *pStack,double *pElem)//浮点数出栈
{
	*pElem=*(pStack->pTop-1);
	pStack->pTop--;
}

Status stack_traverse(Stack *pStack,Status (*visit)(StackElem*))//遍历栈
{
	StackElem* current=pStack->pBase;
	while(current<pStack->pTop)
	{
		if(visit(current)==ERROR){
		return ERROR;
		}
		current++;
	}
	return OK;
}