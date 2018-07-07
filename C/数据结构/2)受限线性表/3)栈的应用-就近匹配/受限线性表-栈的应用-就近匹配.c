#include "SeqStack.h"

// 判断左括号
int is_left(char ch)
{
	return ch == '(';
}

// 判断右括号
int is_right(char ch)
{
	return ch == ')';
}

// 打印错误位置
void printErr(const char *str,const char *err,const char *p) 
{
	printf("Error:%s\n",err);
	printf("%s\n",str);
	int len = p - str;
	for (int i = 0; i < len; i++)
	{
		printf(" ");
	}
	printf("A\n");
}

int main()
{
	const char *str = "5+5*(6)+9/3*1)-(1+3(";

	// 初始化栈
	void *stack = init();
	char *p = (char*)str;

	while (*p != '\0')
	{
		// 如果是左括号, 入栈
		if (is_left(*p))
		{
			push(stack,p);
		}

		// 如果是右括号, 会有两种情况: 1.栈不为空,匹配成功,把栈中的字符弹出
		// 2.栈为空, 这个右括号没有匹配的左括号
		if (is_right(*p))
		{
			if (get_size(stack) > 0) 
			{
				pop(stack);
			}
			else 
			{
				// 打印出错误信息
				printErr(str, "没有匹配到左括号",p);
			}
		}
		p++;
	}

	// 扫描完成字符串, 那么判断栈是否为空
	while (get_size(stack) > 0)
	{
		char *pChar = get_stack_top(stack);
		// 弹出栈顶元素
		pop(stack);
		// 打印错误信息
		printErr(str, "没有匹配到右括号",pChar);
	}

	system("pause");
	return 0;
}