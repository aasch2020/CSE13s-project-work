#include "stats.h"
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i++) {
        int current_index = i;
        int temporary_var = move(stats, A[i]);
        while ((current_index > 0) && (cmp(stats, temporary_var, A[current_index - 1]) == -1)) {
            A[current_index] = move(stats, A[current_index - 1]);
            current_index--;
        }
        A[current_index] = move(stats, temporary_var);
    }
    return;
}
