#include "../include/bubble_sort.h"
#include <stdio.h>

/**
	the key is swap the nearby elements
**/
using namespace charles;
int main()
{
	const int MAX_ELEMENTS = 10;
	int list[MAX_ELEMENTS] = {2,5,12,3,45,1,6,9,7,4};
	printf("The list before sorting is:\n");
	for(int i = 0; i < MAX_ELEMENTS; ++i) {
		printf("%d ",list[i]);
	}
	charls:BubbleSort(list,0,MAX_ELEMENTS-1);
	printf("The list after sorting is:\n");
	for(int i = 0; i < MAX_ELEMENTS; ++i) {
		printf("%d ",list[i]);
	}
	return 0;

}