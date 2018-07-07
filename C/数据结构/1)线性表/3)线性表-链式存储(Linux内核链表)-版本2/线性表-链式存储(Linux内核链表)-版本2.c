#include "Linklist.h"

// 用户的数据, 用户的数据结构体第一个成员必须包含规则的数据
typedef struct Student {
	Node node;
	char name[64];
	int age;
}Student;

// 打印数据
void print_r(void *_data)
{
	Student *data = (Student*)_data;
	printf("name:%s, age:%d\n", data->name, data->age);
}


int main()
{
	Student s1 = { NULL,"Dejan1",10 };
	Student s2 = { NULL,"Dejan2",20 };
	Student s3 = { NULL,"Dejan3",30 };
	Student s4 = { NULL,"Dejan4",40 };
	Student s5 = { NULL,"Dejan5",50 };

	void *list = init();
	// 将数据插入链表
	insert(list, 0, (Node*)&s1);
	insert(list, 0, (Node*)&s2);
	insert(list, 0, (Node*)&s3);
	insert(list, 0, (Node*)&s4);
	insert(list, 0, (Node*)&s5);

	each(list, print_r);

	printf("------ 指定位置3删除节点元素 ------\n");
	remove_by_pos(list, 3);
	each(list, print_r);

	Student *s2_data = get_node(list, 2);
	printf("学生s2的name:%s, 学生s2的age:%d\n", s2_data->name, s2_data->age);
	printf("链表当前节点数size:%d\n", get_size(list));

	// 销毁
	destroy(list);

	system("pause");
	return 0;
}