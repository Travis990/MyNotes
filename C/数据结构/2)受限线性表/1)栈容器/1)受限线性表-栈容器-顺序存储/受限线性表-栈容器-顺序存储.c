#include "SeqStack.h"

// 用户的数据
typedef struct Student {
	char nane[64];
	int age;
}Student;

int main()
{
	Student s1 = { "Dejan1",10 };
	Student s2 = { "Dejan2",20 };
	Student s3 = { "Dejan3",30 };
	Student s4 = { "Dejan4",40 };
	Student s5 = { "Dejan5",50 };

	// 初始化栈
	void *stack = init();

	// 数据入栈
	push(stack, &s1);
	push(stack, &s2);
	push(stack, &s3);
	push(stack, &s4);
	push(stack, &s5);

	// 输出栈中所有的元素
	while (get_size(stack) > 0)
	{
		Student *stu = (Student*)get_stack_top(stack);
		printf("name:%s, age:%d\n",stu->nane,stu->age);
		// 弹出栈顶元素
		pop(stack);
	}

	destroy(stack);

	system("pause");
	return 0;
}