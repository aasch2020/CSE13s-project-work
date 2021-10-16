#include "stats.h"
#include <math.h>
void quick_sort(Stats *stats, uint32_t *A, uint32_t n){
	int start_gap_round_int = log(3 + (2 * n));
	int starting_gap_calculation_value = start_gap_round_int/log(3);
	int gap = ((pow(3, starting_gap_calculation_value) - 1));
	for (int k = gap; k > 0; k--){
		int j = 0;
		uint32_t temp = 0;
		for (uint32_t i = gap; i < n; i++){
			j = i;
			temp =  move(stats, A[i]);

			while ((j >= gap) &&( temp < A[j - gap])){
				A[j] = A[j - gap];
				j -= gap;
			}
			A[j] -=gap;
		}
		gap = (gap - 1)/3;
	}
}
