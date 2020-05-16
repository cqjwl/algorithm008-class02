#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lemonadeChange.h"

bool lemonadeChange(int* bills, int billsSize){
    if (bills == NULL || billsSize <= 0) {
        return true;
    }

    int five_cnt = 0;
    int ten_cnt = 0;
    for (int i = 0; i < billsSize; i++) {
        if (bills[i] == 20) {
            int tmp = 3;
            if (ten_cnt) {
                ten_cnt--;
                tmp -= 2;
            }
            
            if (five_cnt >= tmp) {
                five_cnt -= tmp;
            } else {
                return false;
            }
        } else if (bills[i] == 10) {
            if (five_cnt) {
                five_cnt--;
            } else {
                return false;
            }
            ten_cnt++;
        } else {
            five_cnt++;
        }
    }

    return true;
}
