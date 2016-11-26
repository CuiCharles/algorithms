#ifndef _BUBBLE_SORT_H__
#define _BUBBLE_SORT_H__
#include <assert.h>


namespace charles{

	template<typename T>
	static void BubbleSort(T list[],int start,int end) {
		int i;
		bool swapped;

		assert(start < end);
		do{
			swapped = false;
			for(i = start + 1; i <= end; ++i) {
				if(list[i-1] > list[i]) {
					T tmp = list[i-1];
					list[i-1] = list[i];
					list[i] = tmp;
					swapped = true;
				}
			}

		}while(swapped);
	}
}


#endif