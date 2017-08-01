#include <vector>

typedef int* vptr;

class vtable
{
	vptr voriginal;
	std::vector<int> vreplace;
public:
	vtable() {};
	vtable(void* instance)
	{
		hak(instance);
	}

	void hak(void* instance)
	{
		voriginal = *(vptr*)instance;
		vptr vend = voriginal - 1;
		while (*++vend) vreplace.push_back(*vend);
		*(vptr*)instance = (vptr)&vreplace[0];
	}

	void replace(int index, void* func)
	{
		vreplace[index] = (int)func;
	}

	void clear(int index)
	{
		vreplace[index] = voriginal[index];
	}

	void* original(int index)
	{
		return (void*)voriginal[index];
	}

	int size()
	{
		return vreplace.size();
	}
};
