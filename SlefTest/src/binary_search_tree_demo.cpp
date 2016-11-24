#include "../include/binary_search_tree.h"
#include <time.h>
#include <stdlib.h>

using namespace charles;
int main()
{
	const int MAX_ELEMENTS = 10;
	int key[MAX_ELEMENTS] = {1,2,3,4,5,6,7,8,9,10};
	int value[MAX_ELEMENTS]= {34,2,12,43,25,15,17,24,56,45};

	BST<int,int> t;

	

	int i ;
	for(i = 0;i < MAX_ELEMENTS;++i){
		printf("insert %d->%d\n",key[i],value[i]);
		t.insert(key[i],value[i]);
	}

	t.print_helper();

	for(i = 0; i < MAX_ELEMENTS; i++){
		printf("getting %d->%d\n",key[i], t.find(key[i])->value);
	}

	for(i = 0; i < MAX_ELEMENTS; i++){
		t.deleteKey(key[i]);
		t.print_helper();
		printf("deleted %d\n\n", key[i]);
	}

	return 0;
}