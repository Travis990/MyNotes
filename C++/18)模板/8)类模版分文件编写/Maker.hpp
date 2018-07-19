#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<string>
using namespace std;

template<class NameType, class AgeType>
class Maker
{
public:
	Maker(NameType name, AgeType age);
	void printMaker();
public:
	NameType name;
	AgeType age;
};

template<class NameType, class AgeType>
Maker<NameType, AgeType>::Maker(NameType name, AgeType age)
{
	this->name = name;
	this->age = age;
}

template<class NameType, class AgeType>
void Maker<NameType, AgeType>::printMaker()
{
	cout << "name:" << this->name << " age:" << this->age << endl;
}