#include "stats.h"
#include <stdbool.h>
#include <stdio.h>
uint32_t maximum_child(Stats *stats, uint32_t *A, uint32_t parent_index, uint32_t last){
	uint32_t left = 2 * parent_index;
//	printf("find kid of %d\n", A[parent_index - 1]);
	uint32_t right = left + 1;
	if ((right <= last) && (cmp(stats, A[right - 1], A[left - 1]) == 1)){
		return right;
	}
	else{
	return left;
	}

}
void fix_heap(Stats *stats, uint32_t *A, uint32_t first_index, uint32_t last){
	bool fixed = true;
//	printf("heap fix\n");
	uint32_t parent = first_index;
	uint32_t greatest_child = maximum_child(stats, A, parent, last);
	//printf("%u\n", (last / 2));
	while  ((parent <= (last / 2)) && fixed){
		if (cmp(stats, A[parent - 1], A[greatest_child - 1]) == -1){
//			printf("fix swap %d, %d\n", A[parent - 1], A[greatest_child - 1]);

			swap(stats, &A[parent - 1], &A[greatest_child - 1]);
//			printf("fix swap %d, %d\n", A[parent - 1], A[greatest_child - 1]);

			parent = greatest_child;
			greatest_child = maximum_child(stats, A, parent, last);
		}else{
			fixed = false;
		}
			
	}
}
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last){
//	printf("heap build\n");
	for (uint32_t i = (last / 2); i >= first; i--){
//		printf("build for%u\n",A[i-1]);
		fix_heap(stats, A, i, last);
//	printf("built heap%u, %u, %u, %u \n", A[0], A[1], A[2], A[3]);
	}
}
void heap_sort(Stats *stats, uint32_t *A, uint32_t n){
	uint32_t first_ind = 1;
	uint32_t last = n;
	build_heap(stats, A, first_ind, n);
//	printf("postbld\n");
	for (uint32_t i = last; i > first_ind; i--){
//		printf("end swap %d, %d\n", A[first_ind - 1], A[i - 1]);
		swap(stats, &A[first_ind - 1], &A[i - 1]);
//	printf("end swap %d, %d\n", A[first_ind - 1], A[i - 1]);
//		printf("is gone now %d\n", A[i - 1]);
		fix_heap(stats, A, first_ind, (i - 1));
//			printf("iter heap final%u, %u, %u, %u \n", A[0], A[1], A[2], A[3]);

	}
}
