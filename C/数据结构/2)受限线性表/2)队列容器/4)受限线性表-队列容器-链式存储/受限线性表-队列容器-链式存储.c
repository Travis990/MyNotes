#include "linkQueue.h"

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

	// 初始化队列
	void *queue = init_link_queue();

	// 入队
	push_link_queue(queue, &s1);
	push_link_queue(queue, &s2);
	push_link_queue(queue, &s3);
	push_link_queue(queue, &s4);
	push_link_queue(queue, &s5);

	// 输出队头和队尾元素
	Student *stu1 = (Student*)get_link_queue_head(queue);
	Student *stu2 = (Student*)get_link_queue_tail(queue);
	printf("排在队伍最前的同学stu1->name:%s, stu1->age:%d\n", stu1->name, stu1->age);
	printf("排在队伍最前的同学stu2->name:%s, stu2->age:%d\n", stu2->name, stu2->age);

	printf("-------------------------------\n");

	// 输出队中所有的元素
	while (get_link_queue_size(queue) > 0)
	{
		// 获取队头元素, 因为队头元素才是输出
		Student *stu = (Student*)get_link_queue_head(queue);
		printf("name:%s, age:%d\n", stu->name, stu->age);

		// 弹出队头元素
		pop_link_queue(queue);
	}

	printf("size:%d\n", get_link_queue_size(queue));

	// 销毁队列
	destroy_link_queue(queue);

	system("pause");
	return 0;
}