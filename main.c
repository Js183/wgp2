#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h> 
#include "calculate.h"

void calculate(char* outputFile); // 中缀后缀转换并做计算，函数定义在calculate.c
void print_help(); // 输出帮助信息

int main(int argc, char* argv[])
{
    char* input=NULL;
    char outputFile[100] = ""; // 初始化输出文件名为空

    // 检查命令行参数是否包含 -t 选项
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0)
        {
            if (i + 1 < argc)
            {
                strcpy(outputFile, argv[i + 1]); // 将文件名复制到outputFile
                i++; // 跳过文件名参数
            }
            else
            {
                printf("错误：未提供输出文件名\n");
                return 1;
            }
        }
    }
    // 初始化历史记录
    read_history("History"); // 从文件中加载历史记录
    printf("\033[1;31m请输入命令(可输入help获取操作帮助信息)：\n\033[0m");// 设置文本为粗体红色
    while (1)
    {
        input = readline("");

        if (!input)
        {
            // 如果用户输入为空，继续下一次循环
            continue;
        }
        if (strcmp(input, "help") == 0)
        {
            print_help(); // 输出操作帮助信息
        }
        else if (strcmp(input, "quit") == 0)
        {
            write_history("History");// 保存历史记录到文件
            break; // 退出程序
        }
        else if (strncmp(input, "calculate", 9) == 0)
        {
            // 提取命令行参数，例如：calculate -t result.txt
            char* token = strtok(input, " ");
            while (token != NULL)
            {
                if (strcmp(token, "-t") == 0)
                {
                    token = strtok(NULL, " "); // 获取下一个标记，即文件名
                    if (token != NULL)
                    {
                        strcpy(outputFile, token); // 将文件名复制到outputFile
                    }
                }
                token = strtok(NULL, " "); // 获取下一个标记
            }

            // 判断用户是否提供了输出文件名
            if (outputFile[0] != '\0')
            {
                calculate(outputFile); // 调用处理表达式的函数，传递文件名
            }
            else
            {
                // 用户未提供文件名，允许输入表达式
                printf("您未提供文件名\n");
                calculate(NULL);
            }
        }
        add_history(input);

        free(input); // 释放输入的内存
    }

    // 清理历史记录
    clear_history();

    return 0;
}

void print_help()
{
    printf("操作帮助信息：\n");
    printf("\t输入\"help\"获取帮助信息\n");
    printf("\t输入\"quit\" 退出程序(若已进入calculate，则仅退出calculate）\n");
    printf("\t输入\"calculate -t <file>\" 进入计算，可指定输出文件，也可直接输出计算结果，直至输入quit前一直在计算交互中\n");
    printf("\t通过\"↑,↓\",可以查看历史命令(表达式)\n");
    printf("\t键入\"ctrl+u\"清除当前行\n");
}