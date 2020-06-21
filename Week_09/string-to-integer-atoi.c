#include <stdio.h>
#include <stdlib.h>
#include "myAtoi.h"

int myAtoi(char * str){
    if (str == NULL) {
        return 0;
    }

    int len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    int flag = 1;
    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < len; i++) {
        if (cnt == 0) {
            if(str[i] == '-') {
                flag = -1;
                cnt++;
            } else if (str[i] == '+') {
                cnt++;
            }else if (str[i] >= '0' && str[i] <= '9') {
                int tmp = (str[i] - '0') * flag;
                ans = 10 * ans + tmp;
                cnt++;
            } else if (str[i] == ' ') {
                continue;
            } else {
                break;
            }
        } else {
            if (str[i] >= '0' && str[i] <= '9') {
                int tmp = (str[i] - '0') * flag; 
                if (ans > INT_MAX / 10  || (ans == INT_MAX / 10 && tmp > 7)) {
                    return INT_MAX;
                } else if (ans < INT_MIN / 10 || (ans == INT_MIN / 10 && tmp < -8)) {
                    return INT_MIN;
                }
                ans = 10 * ans + tmp;
                cnt++;
            } else {
                break;
            }
        }
    }

    return ans;
}
