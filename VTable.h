#ifndef vtable

typedef int* vptr;

class vtable
{
	vptr orig; 
	int* copy = 0;
	void* _this;
public:
	int size = 0;

	vtable() {}

	vtable(void* instance) 
	{
		hak(instance);
	}

	~vtable()
	{
		if (copy) delete[] copy;
	}

	void hak(void* instance)
	{
		_this = instance;
		orig = *(vptr*)instance;
		vptr vend = (vptr)orig - 1;
		while (*++vend) size++;
		copy = new int[size];
		memcpy(&copy[0], orig, size * 4);
	}

	void replace(int index, void* func)
	{
		if (*(vptr*)_this == orig) *(vptr*)_this = (vptr)&copy[0];
		copy[index] = (int)func;
	}

	void* original(int index) 
	{
		return (void*)orig[index];
	}

	void clear(int index)
	{
		copy[index] = orig[index];
	}

	void*& operator*()
	{
		return _this;
	}

	void* operator/(int index)
	{
		return (void*)orig[index];
	}
};

#endif
