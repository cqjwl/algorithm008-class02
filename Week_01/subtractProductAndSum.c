#include <stdio.h>
#include <stdlib.h>
#include "subtractProductAndSum.h"

int subtractProductAndSum(int n){
    if (n == 0) {
        return 0;
    }

    int product = 1;
    int sum = 0;
    while (n) {
        int tmp = n % 10;
        product = product * tmp;
        sum = sum + tmp;

        n = n / 10;
    }

    return product - sum;
}
