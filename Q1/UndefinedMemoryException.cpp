#include <iostream>

int main()
{
	// dereferencing NULL pointer is undefined behaviour and will usually cause a segmentation fault
	// force the compiler to derefernce by using it as the return value
	return *(int *)NULL;
}
