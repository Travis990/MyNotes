#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 自定义数据类型
struct Human
{
	char name[64];
	int age;
};

void HumanEatFood(struct Human *h)
{
	printf("%s在吃人饭\n", h->name);
}

struct Animal
{
	char name[64];
	int age;
};

void AnimalEatFood(struct Animal *a)
{
	printf("%s在吃动物饭\n", a->name);
}

int main()
{
	struct Human human = { "人类",1000 };
	struct Animal animal = { "动物", 5 };

	AnimalEatFood(&human);
	AnimalEatFood(&animal);

	system("pause");
	return 0;
}