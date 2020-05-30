#include <stdio.h>
#include <stdlib.h>
#include "canCross.h"

bool canCross(int* stones, int stonesSize){

    bool result = false;
    int i, j, k, m, iK, jK, preK;

    if( stonesSize < 0 || stones == NULL){
        return false;
    }

    if (stonesSize == 2){
        return (stones[0] + 1 == stones[1]) ? true : false;
    }

    int **dp;
    int *dpPre = NULL;
    
    dp = (int**)malloc((stonesSize + 1) * sizeof(int*));  
    
    for(i = 0;i < stonesSize + 1; i++){
        dp[i]=(int*)malloc((stonesSize + 1) * sizeof(int));
        memset(dp[i], -1, sizeof (int) * (stonesSize)); 
    }

    dp[1][0] = (stones[0] + 1 == stones[1]) ? 1 : -1;
    if (dp[1][0] == 1) {
        for(i = 2; i < stonesSize; i++) {
            iK = 0;

            for(j = i - 1; j > 0; j--) {
                k = stones[i] - stones[j];
                dpPre = dp[j];

                for(jK = 0; jK < stonesSize; jK++) {
                    preK = dpPre[jK];
                    if(preK == -1){
                        break;
                    }

                    if((k == preK || k == preK - 1 || k == preK +1)) {
                        dp[i][iK++] = k;
                        break;
                    }
                }
            }
        }

        if(dp[--i][0] != -1){
            result = true;
        }
    }

    for(i=0; i<stonesSize + 1; i++){
        free(dp[i]);   
    }
    free(dp);

    return result;
}
