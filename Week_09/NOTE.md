# 学习笔记

## 动态规划：

与分治类似，也是将待求解的问题分解为若干个子问题，按顺序求解子问题，前一子问题的解，为后一子问题的求解提供了有用的信息。在求解任一子问题时，列出各种可能的局部解，通过决策保留那些有可能达到最优的局部解，丢弃其他局部解。依次解决各子问题，最后一个子问题就是初始问题的解。

动态规划的特点：
1、最优子结构：在自下而上或自顶向下的记忆化递推过程中，求得的每个子问题一定是最优的局部解；
2、状态初始化：先初始化已知状态，从而才能自下而上的递推到原问题得解；
3、状态转移方程：从前一个子问题转化到后一个子问题之间的递推关系；

### 代码模板：

```c
 //状态初始化
 for (i = 0; i <= n; i++) {
     dp[i] = 0;
 }

 //遍历解空间，计算每个子问题的局部最优解
 for (int i = 1; i <= n; i++) {
     for (int j = 1; j <= m; j++) {
         if (!condition1) {
             dp[i] = dp[i - 1];
         } else {
             dp[i] = max (或min)(dp[i - 1], dp[i - 1] + ... );
         }
    }
}

return dp[n];
```

### 代码实践：

##### [63. 不同路径 II](https://leetcode-cn.com/problems/unique-paths-ii/)

`dp[i][j]` 代表能达到这个点的路径数， i， j分别为x轴坐标和y轴坐标。

状态转移方程：`dp[i][j] = dp[i - 1][j] + dp[i][j - 1];` 
当遇到障碍的时候`obstacleGrid[i][j] == 1`，障碍点的路径数置为0，`dp[i][j] = 0`；

边界处理：
`dp[0][0]`到`dp[m-1][0]`，`dp[i][0] = dp[i - 1][0]`；
`dp[0][0]`到`dp[0][m-1]`，`dp[0][j] = dp[0][j - 1]`；

```c
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize){
    int n = obstacleGridSize;
    int m = obstacleGridColSize[0];
    if (n == 0 || m == 0) {
        return 0;
    }

    if (obstacleGrid[0][0] == 1 || obstacleGrid[n - 1][m - 1] == 1) {
        return 0;
    }

    if (n == 1 || m == 1) {
        return 1;
    }

    long dp[n][m];
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (obstacleGrid[i][j] == 1) {
                dp[i][j] = 0;
                continue;
            }
            if (i == 0 && j > 0) {
                dp[i][j] = dp[i][j - 1];
            } else if (j == 0 && i > 0) {
                dp[i][j] = dp[i - 1][j];
            } else if (i > 0 && j > 0){
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }

    return dp[n - 1][m - 1];
}
```

#### 股票买卖

（以下内容摘录自：[labuladong](https://leetcode-cn.com/u/labuladong/)发布的题解 [一个方法团灭 6 道股票问题](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-l-3/) ）

```c
作者：labuladong
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-l-3/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

6 道股票买卖问题是有共性的，通过对第四题（限制最大交易次数为 k）是一个最泛化的形式，其他的问题都是这个形式的简化。

第一题是只进行一次交易，相当于 k = 1；

第二题是不限交易次数，相当于 k = +infinity（正无穷）；

第三题是只进行 2 次交易，相当于 k = 2；

剩下两道也是不限次数，但是加了交易「冷冻期」和「手续费」的额外条件，其实就是第二题的变种；

每天都有三种「选择」：买入、卖出、无操作，用 buy, sell, rest 表示这三种选择。但问题是，并不是每天都可以任意选择这三种选择的，因为 sell 必须在 buy 之后，buy 必须在 sell 之后。那么 rest 操作还应该分两种状态，一种是 buy 之后的 rest（持有了股票），一种是 sell 之后的 rest（没有持有股票）。而且别忘了，还有交易次数 k 的限制，就是说你 buy 还只能在 k > 0 的前提下操作。

问题的「状态」有三个，第一个是天数，第二个是允许交易的最大次数，第三个是当前的持有状态（即之前说的 rest 的状态，我们不妨用 1 表示持有，0 表示没有持有）。然后用一个三维数组就可以装下这几种状态的全部组合：

```c
dp[i][k][0 or 1]
0 <= i <= n-1, 1 <= k <= K
n 为天数，大 K 为最多交易数
此问题共 n × K × 2 种状态，全部穷举就能搞定。

for 0 <= i < n:
    for 1 <= k <= K:
        for s in {0, 1}:
            dp[i][k][s] = max(buy, sell, rest)
```

用自然语言描述出每一个状态的含义，比如说 `dp[3][2][1]` 的含义就是：今天是第三天，现在手上持有着股票，至今最多进行 2 次交易。再比如 `dp[2][3][0]` 的含义：今天是第二天，现在手上没有持有股票，至今最多进行 3 次交易。

状态转移方程：

```c
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
              max(   选择 rest  ,           选择 sell      )

解释：今天我没有持有股票，有两种可能：
要么是我昨天就没有持有，然后今天选择 rest，所以我今天还是没有持有；
要么是我昨天持有股票，但是今天我 sell 了，所以我今天没有持有股票了。

dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
              max(   选择 rest  ,           选择 buy         )

解释：今天我持有着股票，有两种可能：
要么我昨天就持有着股票，然后今天选择 rest，所以我今天还持有着股票；
要么我昨天本没有持有，但今天我选择 buy，所以今天我就持有股票了。
```

定义 base case，即最简单的情况：

```c
dp[-1][k][0] = 0
解释：因为 i 是从 0 开始的，所以 i = -1 意味着还没有开始，这时候的利润当然是 0 。
dp[-1][k][1] = -infinity
解释：还没开始的时候，是不可能持有股票的，用负无穷表示这种不可能。
dp[i][0][0] = 0
解释：因为 k 是从 1 开始的，所以 k = 0 意味着根本不允许交易，这时候利润当然是 0 。
dp[i][0][1] = -infinity
解释：不允许交易的情况下，是不可能持有股票的，用负无穷表示这种不可能。
```

把上面的状态转移方程总结一下：

```c
base case：
dp[-1][k][0] = dp[i][0][0] = 0
dp[-1][k][1] = dp[i][0][1] = -infinity

状态转移方程：
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
```

##### [121. 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

**k = 1** 直接套状态转移方程，根据 base case，可以做一些简化：

```c
dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i]) 
            = max(dp[i-1][1][1], -prices[i])
解释：k = 0 的 base case，所以 dp[i-1][0][0] = 0。

现在发现 k 都是 1，不会改变，即 k 对状态转移已经没有影响了。
可以进行进一步化简去掉所有 k：
dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
dp[i][1] = max(dp[i-1][1], -prices[i])
```

```c
int maxProfit(int* prices, int pricesSize){
    int n = pricesSize;
    if (n <= 1) {
        return 0;
    }

    int dp[n][2];
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            dp[0][0] = 0;
            dp[0][1] = -prices[i];
            continue;
        }
        dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        dp[i][1] = fmax(dp[i - 1][1], -prices[i]);
    }

    return dp[n - 1][0];
}

int maxProfit(int* prices, int pricesSize){
    int n = pricesSize;
    if (n <= 0) {
        return 0;
    }

    int dp[2];
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            dp[0] = 0;
            dp[1] = -prices[i];
            continue;
        }
        dp[0] = fmax(dp[0], dp[1] + prices[i]);
        dp[1] = fmax(dp[1], -prices[i]);
    }

    return dp[0];
}
```

##### [122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

**k = +infinity** 如果 k 为正无穷，那么就可以认为 k 和 k - 1 是一样的。可以这样改写框架：

```c
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
            = max(dp[i-1][k][1], dp[i-1][k][0] - prices[i])

我们发现数组中的 k 已经不会改变了，也就是说不需要记录 k 这个状态了：
dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
```

```c
int maxProfit(int* prices, int pricesSize){
    int n = pricesSize;
    if (n <= 1) {
        return 0;
    }

    int dp[n][2];
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            dp[0][0] = 0;
            dp[0][1] = -prices[i];
            continue;
        }
        dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }

    return dp[n - 1][0];
}

int maxProfit(int* prices, int pricesSize){
    int n = pricesSize;
    if (n <= 1) {
        return 0;
    }

    int dp[2];
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            dp[0] = 0;
            dp[1] = -prices[i];
            continue;
        }
        dp[0] = fmax(dp[0], dp[1] + prices[i]);
        dp[1] = fmax(dp[1], dp[0] - prices[i]);
    }

    return dp[0];
}
```

##### [123. 买卖股票的最佳时机 III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/)

**k = 2**  每次 sell 之后要等一天才能继续交易。只要把这个特点融入上一题的状态转移方程即可：

```c
原始的动态转移方程，没有可化简的地方
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
```

```c
int maxProfit(int* prices, int pricesSize){
    int n = pricesSize;
    if (n <= 1) {
        return 0;
    }

    int max_k = 2;
    int dp[n][max_k + 1][2];
    for (int k = 1; k < max_k + 1; k++) {
        dp[0][k][0] = 0;
        dp[0][k][1] = -prices[0];
    }

    for (int i = 1; i < pricesSize; i++){
        for (int k = 1; k < max_k + 1; k++) {
            if ( k - 1 == 0 ) {
                dp[i][k][0] = fmax(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
                dp[i][k][1] = fmax(dp[i - 1][k][1], -prices[i]);
                continue;
            }
            dp[i][k][0] = fmax(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
            dp[i][k][1] = fmax(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
        }
    }

    return dp[n - 1][max_k][0];
}
```

##### [714. 买卖股票的最佳时机含手续费](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

**k = +infinity with fee**  每次交易要支付手续费，只要把手续费从利润中减去即可。改写方程：

```c
dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)
解释：相当于买入股票的价格升高了。
在第一个式子里减也是一样的，相当于卖出股票的价格减小了。
```

```c
int maxProfit(int* prices, int pricesSize, int fee){
    int n = pricesSize;
    if (n <= 1) {
        return 0;
    }

    int dp[n][2];
    dp[0][0] = 0;
    dp[0][1] = -prices[0] - fee;
    for (int i = 1; i < n; i++) {
        dp[i][0] = fmax (dp[i - 1][0], dp[i - 1][1] + prices[i]);
        dp[i][1] = fmax (dp[i - 1][1], dp[i - 1][0] - prices[i] - fee);
    }

    return dp[n - 1][0];
}
```

##### [309. 最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

**k = +infinity with cooldown**  每次 sell 之后要等一天才能继续交易。只要把这个特点融入上一题的状态转移方程即可：

```c
dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
解释：第 i 天选择 buy 的时候，要从 i-2 的状态转移，而不是 i-1 。
```

```c
int maxProfit(int* prices, int pricesSize){
    int n = pricesSize;
    if (n <= 1) {
        return 0;
    }

    int dp[n][2];
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i < n; i++) {
        if (i - 2 == -1) {
            dp[i][0] = fmax (dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = fmax (dp[i - 1][1], -prices[i]);
            continue;            
        }
        dp[i][0] = fmax (dp[i - 1][0], dp[i - 1][1] + prices[i]);
        dp[i][1] = fmax (dp[i - 1][1], dp[i - 2][0] - prices[i]);
    }

    return dp[n - 1][0];
}
```

##### [188. 买卖股票的最佳时机 IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/)

**k = any integer**  传入的 k 值会非常大，dp 数组太大了。现在想想，交易次数 k 最多有多大呢？

一次交易由买入和卖出构成，至少需要两天。所以说有效的限制 k 应该不超过 n/2，如果超过，就没有约束作用了，相当于 k = +infinity。

```c
原始的动态转移方程，没有可化简的地方
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
```

```c
int maxProfit_k_inf(int* prices, int pricesSize) {
    int n = pricesSize; 
    if (n <= 1) {
        return 0;
    }

    int dp0 = 0;
    int dp1 = INT_MIN;
    for (int i = 0; i < n; i++) {
        int tmp = dp0;
        dp0 = fmax(dp0, dp1 + prices[i]);
        dp1 = fmax(dp1, tmp - prices[i]);
    }

    return dp0;
}

int maxProfit(int k, int* prices, int pricesSize){
    int n = pricesSize; 
    if (n <= 1 || k <= 0) {
        return 0;
    }

    if (k > n / 2) {
        return maxProfit_k_inf(prices, pricesSize);
    }
    
    int max_k = k;
    int dp[n][max_k + 1][2];
    for (int k = 1; k < max_k + 1; k++) {
        dp[0][k][0] = 0;
        dp[0][k][1] = -prices[0];
    }

    for (int i = 1; i < pricesSize; i++){
        for (int k = 1; k < max_k + 1; k++) {
            if ( k - 1 == 0 ) {
                dp[i][k][0] = fmax(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
                dp[i][k][1] = fmax(dp[i - 1][k][1], -prices[i]);
                continue;
            }
            dp[i][k][0] = fmax(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
            dp[i][k][1] = fmax(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
        }
    }

    return dp[n - 1][max_k][0];
}
```

