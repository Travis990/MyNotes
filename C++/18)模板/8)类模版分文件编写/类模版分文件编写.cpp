#include "Maker.hpp" // 常用，

/*
这里编译一次
template<class NameType, class AgeType>
class Maker
{
public:
	Maker(NameType name, AgeType age);
	void printMaekr();
public:
	NameType name;
	AgeType age;
};
*/

int main()
{
	// 这里调用时，生成模版类，需要编译器一次
	Maker<string, int> m("小姐姐", 20);
	m.printMaker();

	system("pause");
	return 0;
}