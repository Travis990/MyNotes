#include "DynamicArray.h"

// 用户的数据
typedef struct Student {
	char name[64];
	int age;
}Student;

// 数组打印
void arr_print(void *data) 
{
	Student *student = (Student*)data;
	printf("name=%s,age=%d\n", student->name, student->age);
}

// 内容比对
void arr_compare(void *_s1, void *_s2)
{
	Student *s1 = (Student*)_s1;
	Student *s2 = (Student*)_s2;

	return (strcmp(s1->name, s2->name) == 0) && (s1->age == s2->age);
}

int main()
{
	// 用户数据
	Student s1 = { "Dejan01", 11 };
	Student s2 = { "Dejan02", 12 };
	Student s3 = { "Dejan03", 13 };
	Student s4 = { "Dejan04", 14 };
	Student s5 = { "Dejan05", 15 };
	Student s6 = { "Dejan06", 16 };
	Student s7 = { "Dejan07", 17 };
	Student s8 = { "Dejan08", 18 };
	Student s9 = { "Dejan09", 19 };
	Student s10 = { "Dejan10", 20 };

	// 初始化数组
	void *arr = init_array();

	printf("------- 插入元素 -------\n");
	insert(arr, 0, &s1);
	insert(arr, 0, &s2);
	insert(arr, 0, &s3);
	each(arr, arr_print);
	printf("------- 头插 -------\n");
	push_front(arr,&s4);
	each(arr, arr_print);
	printf("------- 尾插 -------\n");
	push_back(arr, &s5);
	each(arr, arr_print);
	printf("数组当前容量(capacity): %d,当前元素个数:%d\n", get_capacity(arr), get_size(arr));
	printf("------- 指定位置插入元素 -------\n");
	insert(arr, 2, &s6); // 插到中间
	each(arr, arr_print);
	printf("------- 头删除 -------\n");
	pop_front(arr);
	each(arr, arr_print);
	printf("------- 尾删除 -------\n");
	pop_back(arr);
	each(arr, arr_print);
	printf("------- 指定位置2删除 -------\n");
	remove_by_pos(arr,2);
	each(arr, arr_print);
	printf("------- 指定值删除 name=Dejan06,age=16 -------\n");
	remove_by_val(arr,&s6, arr_compare);
	each(arr, arr_print);

	// 销毁,释放空间
	destroy_array(arr);

	system("pause");
	return 0;
}