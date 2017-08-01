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

void* myhook(int aa, int g)
{
	printf("hack function called %d %d\n",aa, g);
	return hackFuncf(nigger.original(0))(6,5);
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

