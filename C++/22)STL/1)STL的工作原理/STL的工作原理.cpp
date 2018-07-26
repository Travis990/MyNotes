#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 容器
template<class T>
class Dejan
{
public:
	typedef T* iterator; // 包装一下原生指针
	Dejan()
	{
		Capacity = 10;
		Size = 10;

		p = new T[Capacity];

		for (int i = 0; i < 10; i++)
		{
			p[i] = i + 1;
		}
	}

	// 容器提供迭代器

	// 提供开始位置的迭代器
	T* begin()
	{
		return p;
	}

	// 提供结束位置的迭代器
	T* end()
	{
		return p + Size;
	}

public:
	T *p;
	int Capacity;
	int Size;
};

// 算法
template<class T>
void Myforeach(T begin, T end)
{
	for (; begin != end; ++begin)
	{
		cout << *begin << " ";
	}
	cout << endl;
}

void test()
{
	// 实例化一个对象，生成一个容器
	Dejan<int> dejan;

	// 获取容器提供的迭代器
	// T*=dejan.begin();
	Dejan<int>::iterator begin = dejan.begin();
	// T*=dejan.end();
	Dejan<int>::iterator end = dejan.end();

	// 算法通过迭代器来使用容器中的数据
	Myforeach(begin, end);
}

int main()
{
	test();

	system("pause");
	return 0;
}