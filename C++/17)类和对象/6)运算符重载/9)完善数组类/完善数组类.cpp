#include "Myarr.h"

void printMyarr(Myarr &arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr.getPosByVal(i) << " ";
	}
	cout << endl;
}

void test()
{
	/*int arr[3] = { 1, 2, 3 };
	arr[0] = 10;
	int ret = arr[2];
	cout << arr[2] << endl;*/

	Myarr arr;
	for (int i = 0; i < arr.getCapacity(); i++)
	{
		arr[i] = i + 1;
	}
	for (int i = 0; i < arr.getCapacity(); i++)
	{
		cout << arr[i] << endl;
	}
}

int main()
{
	test();

	system("pause");
	return 0;
}