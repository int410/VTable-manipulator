#include <iostream>
#include "VTable.h"

using namespace std;

typedef void* (*hackFuncf)(int, int);

vtable nigger;

class Base
{
public:
	virtual void* Test(int, int) = 0;
	virtual void Test1() = 0;
};

class Derived : public Base
{
public:
	int variable;

	void* Test(int a, int b)
	{
		cout << "original func called " << endl;
		return (void*)a;
	}
	void Test1()
	{
		cout << "original-2 func called \n";
	}
};

void* myhook(int arg1, int arg2)
{
	printf("hack function called %d %d\n",arg1, arg2);
	
	return hackFuncf(nigger.original(0))(arg1,arg2);
}

int main()
{
	Derived* inst = new Derived;

	nigger.hak(inst);
	nigger.replace(0, myhook);

	printf("result = %d\n", inst->Test(5, 77));

	delete inst;

	system("pause");

	return 0;
}

/*
эту функцию легко вызвать внешне, потому что она никак не взаимодейтсвует
с экземляром класса, но что делать в обратном случае?
перед вызовом, нужно передать адрес экземпляра класса в регистр ecx
сделать это можно так:
__asm mov ecx inst
"вызов функции"
или же использовать способ вызова __thiscall:
typedef void* (__thiscall *hackFuncf)(void*, int, int);
и первым аргументом передавать inst:
hackFuncf(nigger.original(index))(inst,arg1,arg2);
далее может возникнуть проблема с очищением стека после фунции
а именно нам нужен ret 8, вместо ret
решить можно с помощью __fastcall, он как раз использует ret 8
но тогда первыми 2мя аргументами функции будут значения ecx и edx
ecx нам как раз нужен, второй пропускаем:
void* __fastcall myhook(void* ecx, void*, int arg1, int arg2) {...}
*/
