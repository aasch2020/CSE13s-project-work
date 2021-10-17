#include "stats.h"
#include <math.h>
#include <stdio.h>
void shell_sort(Stats *stats, uint32_t *A, uint32_t n){
	int start_gap_round_int = log(3 + (2 * n));
	int starting_gap_calculation_value = start_gap_round_int/log(3);
	int gap = ((pow(3, starting_gap_calculation_value) - 1));
	for (int k = starting_gap_calculation_value; k > 0; k--){
		int j = 0;
		uint32_t temp = 0;
		for (uint32_t i = (gap/2); i < n; i++){
			j = i;
			temp =  move(stats, A[i]);

			while ((j >= (gap/2)) && ((cmp(stats, temp, A[j - (gap/2)]) == -1))){
				A[j] = move(stats, A[j - (gap/2)]);
				j = j - (gap/2);
			}
			A[j] = move(stats, temp);
		}
		gap = (gap - 1)/3;
	}
}
