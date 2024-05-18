#include <string.h>
#include "high_scores.h"

int32_t latest(const int32_t* scores, size_t scores_len) {
    if (!scores || !scores_len) return 0;
    return scores[scores_len - 1];
}

int32_t personal_best(const int32_t* scores, size_t scores_len) {
    if (!scores || !scores_len) return 0;

    int32_t max = *scores;
    for (size_t i = 1; i < scores_len; ++i) {
        max = scores[i] > max ? scores[i] : max;
    }
    return max;
}

static size_t get_min_index(const int32_t scores[3]) {
    if (scores[0] <= scores[1] && scores[0] <= scores[2]) return 0;
    else if (scores[1] <= scores[0] && scores[1] <= scores[2]) return 1;
    else return 2;
}

static void simple_sort(int32_t arr[3]) {
    if (arr[0] < arr[1]) {
        int temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
    }
    if (arr[1] < arr[2]) {
        int temp = arr[1];
        arr[1] = arr[2];
        arr[2] = temp;
    }
    if (arr[0] < arr[1]) {
        int temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
    }
}

size_t personal_top_three(const int32_t* scores, size_t scores_len,
                          int32_t* output) {
    memset(output, 0, sizeof(*output) * 3);
    for (size_t i = 0; i < scores_len; ++i) {
        const size_t min_i = get_min_index(output);
        if (scores[i] > output[min_i]) {
            output[min_i] = scores[i];
        }
    }
    simple_sort(output);
    return scores_len < 3 ? scores_len : 3;
}
