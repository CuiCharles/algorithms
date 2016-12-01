#include "../include/2darray.h"
#include <iostream>

using namespace charles;
int main(){
	Array2D<int> arr(4,4);
	arr.clear(1);
	arr.printArray();

	std::cout << arr(3,3) << std::endl;

	return 0;
}