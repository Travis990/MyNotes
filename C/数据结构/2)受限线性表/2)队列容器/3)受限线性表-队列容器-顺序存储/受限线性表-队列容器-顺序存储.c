#include "SeqQueue.h"

// 用户的数据
typedef struct Student {
	char name[64];
	int age;
}Student;

int main()
{
	Student s1 = { "Dejan1",10 };
	Student s2 = { "Dejan2",20 };
	Student s3 = { "Dejan3",30 };
	Student s4 = { "Dejan4",40 };
	Student s5 = { "Dejan5",50 };

	// 初始化队列
	void *queue = init();

	// 入队
	push(queue, &s1);
	push(queue, &s2);
	push(queue, &s3);
	push(queue, &s4);
	push(queue, &s5);

	// 输出队头和队尾元素
	Student *stu1 = (Student*)get_queue_head(queue);
	Student *stu2 = (Student*)get_queue_tail(queue);
	printf("排在队伍最前的同学stu1->name:%s, stu1->age:%d\n", stu1->name, stu1->age);
	printf("排在队伍最后的同学stu2->name:%s, stu2->age:%d\n", stu2->name, stu2->age);

	printf("-------------------------------\n");

	// 输出队中所有的元素
	while (get_size(queue) > 0)
	{
		// 获取队头元素, 因为队头元素才是输出
		Student *stu = (Student*)get_queue_head(queue);
		printf("name:%s, age:%d\n", stu->name, stu->age);

		// 弹出队头元素
		pop(queue);
	}

	printf("size:%d\n", get_size(queue));

	destroy(queue);

	system("pause");
	return 0;
}