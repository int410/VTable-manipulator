#include <vector>

typedef int* vptr;

class vtable
{
	vptr orig; // указатель на оригинал v-tabl'a
	std::vector<int> copy;
public:
	vtable() {};
	vtable(void* instance)
	{
		hak(instance);
	}

	void hak(void* instance)
	{
		orig = *(vptr*)instance;
		vptr vend = (vptr)orig - 1;
		while (*++vend) copy.push_back(*vend);
		*(vptr*)instance = (vptr)&copy[0];
	}

	void replace(int index, void* func)
	{
		copy[index] = (int)func;
	}

	void clear(int index)
	{
		copy[index] = orig[index];
	}

	void* original(int index)
	{
		return (void*)orig[index];
	}

	int size()
	{
		return copy.size();
	}
};
