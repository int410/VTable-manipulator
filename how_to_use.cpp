#include <iostream>
#include "VTable.h"

using namespace std;

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

void* __fastcall myhook(void* ecx, void* edx, int arg1, int arg2)
{
	printf("hook called: %d, %d\n", arg1, arg2);

	auto func = (void*(__thiscall*)(void*, int, int))(nigger.original(0));
	return func(ecx, 4, 5);
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
