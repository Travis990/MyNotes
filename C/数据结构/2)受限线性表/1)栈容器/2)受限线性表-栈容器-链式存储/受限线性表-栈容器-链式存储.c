#include "LinkStack.h"

// 用户的数据
typedef struct Student {
	Node node;
	char name[64];
	int age;
}Student;

int main()
{
	Student s1 = { NULL,"Dejan1",10 };
	Student s2 = { NULL,"Dejan2",20 };
	Student s3 = { NULL,"Dejan3",30 };
	Student s4 = { NULL,"Dejan4",40 };
	Student s5 = { NULL,"Dejan5",50 };

	// 初始化链表
	void *stack = init();

	// 入栈
	push(stack, &s1);
	push(stack, &s2);
	push(stack, &s3);
	push(stack, &s4);
	push(stack, &s5);

	while (get_size(stack) > 0)
	{
		// 获取栈顶元素
		Student *stu = get_stack_top(stack);
		printf("name:%s, age:%d\n", stu->name, stu->age);
		// 弹出栈顶元素
		pop(stack);
		printf("size:%d\n", get_size(stack));
	}

	destroy(stack);

	system("pause");
	return 0;
}