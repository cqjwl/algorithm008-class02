#include <stdio.h>
#include <stdlib.h>
#include "maxProfit.h"

int maxProfit(int* prices, int pricesSize){
    if (maxProfit == NULL || pricesSize <= 0) {
        return 0;
    }

    int result = 0;
    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] > prices[i - 1]) {
            result += prices[i] - prices[i - 1];
        }
    }

    return result;
}
