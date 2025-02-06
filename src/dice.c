#include <stdio.h>
#include <stdlib.h>

double dice_coef(int* groundtruth_mask, int* pred_mask, int size) {
    int intersect = 0;
    int total_sum = 0;

    for (int i = 0; i < size; i++) {
        intersect += pred_mask[i] * groundtruth_mask[i];
        total_sum += pred_mask[i] + groundtruth_mask[i];
    }

    double dice = (2.0 * intersect) / total_sum;

    return ((int)(dice * 1000 + 0.5)) / 1000.0;
}