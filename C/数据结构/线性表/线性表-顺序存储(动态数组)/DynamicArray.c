#include "DynamicArray.h"

// 初始化动态数组函数
void* init_array()
{
	DA *arr = (DA*)malloc(sizeof(DA));
	if ( NULL == arr )
	{
		printf("malloc error!");
		return -1;
	}
	arr->capacity = 10; // 初始化容量
	arr->size = 0; // 初始化元素个数
	arr->data = malloc(sizeof(void*) * arr->capacity); // 申请指针数组
	return arr;
}

// 指定位置插入数据
int insert(void *_arr, int _pos, void *_data) 
{
	if ( NULL == _arr || NULL == _data )
	{
		return -1;
	}
	DA *arr = (DA*)_arr; // 改变步长

	// 容错,如果位置不对,就让插入的位置等于 arr->size
	if ( 0 > _pos || _pos > arr->size )
	{
		_pos = arr->size;
	}
	
	// 判断容量是否足够
	if ( arr->size == arr->capacity )
	{
		// 容量已经满了
		// 根据增长空间策略
		int newcapacity = arr->size * 2;
		void **newspace = (void**)malloc(sizeof(void*) * newcapacity);
		// 将旧空间的数据拷贝到新空间
		memcpy(newspace, arr->data, sizeof(void*) * arr->capacity);
		// 释放旧空间
		free(arr->data);
		// 更新核心数据
		arr->data = newspace;
		arr->capacity = newcapacity;
	}

	// 移动元素,空出位置来放数据
	for (int i = arr->size - 1; i >= _pos; i--)
	{
		arr->data[i + 1] = arr->data[i];
	}

	// 将元素插入
	arr->data[_pos] = _data;

	// 维护元素个数
	arr->size++;

	return 0;
}

// 头部插入
int push_front(void *_arr, void *_data)
{
	return insert(_arr, 0, _data);
}

// 尾部插入
int push_back(void *_arr, void *_data)
{
	DA *arr = (DA*)_arr;
	return insert(_arr, arr->size, _data);
}

// 指定位置删除,下标以0开始
int remove_by_pos(void *_arr, int _pos)
{
	if ( NULL == _arr )
	{
		return -1;
	}
	DA *arr = (DA*)_arr;
	if ( 0 == arr->size) // 没有元素
	{
		return -2;
	}
	// 判断位置是否合法
	if ( 0 > _pos || _pos > arr->size -1 )
	{
		return -3;
	}
	// 移动元素来删除元素
	for (int i = _pos; i < arr->size - 1; i++)
	{
		arr->data[i] = arr->data[i + 1];
	}
	arr->size--;
	return 0;
}

// 根据值来删除,第三个参数是需要用户传入函数地址
int remove_by_val(void *_arr, void *_data, compare *_compare)
{
	if ( NULL == _arr || NULL == _data || NULL == _compare)
	{
		return -1;
	}
	DA *arr = (DA*)_arr;
	for (int i = 0; i < arr->size; i++)
	{
		if (_compare(arr->data[i], _data))
		{
			remove_by_pos(arr, i);
			break;
		}
	}
	return 0;
}

// 头部删除
int pop_front(void *_arr)
{
	return remove_by_pos(_arr, 0);
}

// 尾部删除
int pop_back(void *_arr)
{
	DA *arr = (DA*)_arr;
	return remove_by_pos(_arr, arr->size - 1);
}

// 获取数组的大小
int get_size(void *_arr)
{
	DA *arr = (DA*)_arr;
	return arr->size;
}

// 获取容量
int get_capacity(void *_arr)
{
	DA *arr = (DA*)_arr;
	return arr->capacity;
}

// 打印数据的函数
void each(void *_arr, void(*foreach)(void*))
{
	if ( NULL == _arr || NULL == foreach )
	{
		return;
	}
	DA *arr = (DA*)_arr;
	for (size_t i = 0; i < arr->size; i++)
	{
		foreach(arr->data[i]);
	}
}

// 销毁数组
int destroy_array(void *_arr)
{
	if ( NULL == _arr)
	{
		return -1;
	}

	DA *arr = (DA*)_arr;
	if ( arr->data != NULL )
	{
		arr->capacity = 0;
		arr->size = 0;
		free(arr->data);
	}
	free(arr);
	arr = NULL;
	return 0;
}