# 学习笔记

## 深度优先搜索：

### 代码模板：

#### 递归写法

```python
 visited = set() 

def dfs(node, visited):
    if node in visited: # terminator
    	# already visited 
    	return 

	visited.add(node) 

	# process current node here. 
	...
	for next_node in node.children(): 
		if next_node not in visited: 
			dfs(next_node, visited)
```

#### 非递归写法

```python
 def DFS(self, tree): 

	if tree.root is None: 
		return [] 

	visited, stack = [], [tree.root]

	while stack: 
		node = stack.pop() 
		visited.add(node)

		process (node) 
		nodes = generate_related_nodes(node) 
		stack.push(nodes) 

	# other processing work 
	...
```

### 代码实践：

#### [200. 岛屿数量](https://leetcode-cn.com/problems/number-of-islands/)

顺序判断grid[i][j]值为‘1’时，cnt计数加1,同时通过DFS将相邻为‘1’的grid[][]置为‘0’，避免被后续搜索又计算为新的岛屿；

```c
void dfs(char** grid, int m, int n, int i, int j, int** visited) {
    if (grid[i][j] == '0') {
        visited[i][j] = 1;
        return;
    }

    grid[i][j] = '0';
    visited[i][j] = 1;
    if (i - 1 >= 0 && visited[i - 1][j] == 0) {
        dfs(grid, m, n, i - 1, j, visited);
    }

    if (i + 1 < m && visited[i + 1][j] == 0) {
        dfs(grid, m, n, i + 1, j, visited);
    }

    if (j - 1 >= 0 && visited[i][j - 1] == 0) {
        dfs(grid, m, n, i, j - 1, visited);
    }

    if (j + 1 < n && visited[i][j + 1] == 0) {
        dfs(grid, m, n, i, j + 1, visited);
    }

    return;
}

int numIslands(char** grid, int gridSize, int* gridColSize){
    if (gridSize <= 0 || gridColSize[0] <= 0) {
        return 0;
    }

    int m = gridSize;
    int n = gridColSize[0];

    int visited[m + 1][n + 1];
    memset(visited, 0, sizeof(int) * (m + 1) * (n + 1));

    int *pvisited[m + 1];
    for (int i = 0; i < m; i++){
        pvisited[i] = &visited[i];
    }
 
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j] == 1) {
                continue;
            } else {
                if (grid[i][j] == '1') {
                    cnt++;
                    dfs(grid, m, n, i, j, pvisited);
                } else {
                    visited[i][j] = 1;
                }
            }
        }
    }

    return cnt;
}
```

## 广度优先搜索：

### 代码模板：

```java
def BFS(graph, start, end):
    visited = set()
	queue = [] 
	queue.append([start]) 

	while queue: 
		node = queue.pop() 
		visited.add(node)

		process(node) 
		nodes = generate_related_nodes(node) 
		queue.push(nodes)

	# other processing work 
	...
```

### 代码实践：

#### [127. 单词接龙](https://leetcode-cn.com/problems/word-ladder/)

采用如下深度优先搜索，即便已优化为超过当前最小值，直接放弃进一步搜索，也会出现超时，已查到相关原因分析和优化方法，有待后续进一步学习；

```c
#define MAX_STACK_SIZE 100000

bool isMatch(char *a, char *b) {
    int alen = strlen(a);
    int cnt = 0;
    for (int i = 0; i < alen; i++) {
        if (a[i] != b[i]) {
            cnt++;
            if (cnt > 1) {
                return false;
            }
        }
    }

    return cnt == 1;
}

void dfs(char * beginWord, char * endWord, char ** wordList, int m, int cnt, int* visited, int* result) {
    if (strcmp(beginWord, endWord) == 0) {
        result[0] = fmin(result[0], cnt);
        return;
    }

    for (int i = 0; i < m; i++) {
        if (visited[i] == 1) {
            continue;
        } else {
            if (isMatch(beginWord, wordList[i])) {
                if (cnt + 1 >= result[0]) {
                    continue;
                }
                visited[i] = 1;
                dfs(wordList[i], endWord, wordList, m, cnt + 1, visited, result);
            }
        }
    }
    
    return;
}

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){
    if (beginWord == NULL || endWord == NULL || wordListSize <= 0) {
        return 0;
    }

    for (int i = 0; i < wordListSize; i++) {
        if (strcmp(endWord, wordList[i]) == 0) {
            break;
        }
        if (i == wordListSize - 1) {
            return 0;
        }
    }

    int m = wordListSize;
    int visited[m + 1];
    memset(visited, 0, sizeof(int) * (m + 1));
    int result = INT_MAX;
    int cnt = 1;
    dfs(beginWord, endWord, wordList, m, cnt, visited, &result);
    if (result == INT_MAX) {
        return 0;
    } else {
        return result;
    }
}
```

改为采用如下广度优先搜索，也即每一层都完成所有可能搜索，找到符合最终条件的也即是最短路径的；

```c
#define QUEUE_SIZE 100000

bool isMatch(char *a, char *b) {
    int alen = strlen(a);
    int cnt = 0;
    for (int i = 0; i < alen; i++) {
        if (a[i] != b[i]) {
            cnt++;
            if (cnt > 1) {
                return false;
            }
        }
    }

    return cnt == 1;
}

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){
    if (beginWord == NULL || endWord == NULL || wordListSize <= 0) {
        return 0;
    }

    for (int i = 0; i < wordListSize; i++) {
        if (strcmp(endWord, wordList[i]) == 0) {
            break;
        }
        if (i == wordListSize - 1) {
            return 0;
        }
    }

    int m = wordListSize;
    int visited[m + 1];
    memset(visited, 0, sizeof(int) * (m + 1));

    int cnt = 1;
    char* queue[QUEUE_SIZE] = {0};
    int inIndex = 0;
    int outIndex = 0;
    queue[inIndex++] = beginWord;
    while (outIndex < inIndex) {
        int len = inIndex - outIndex;
        for (int i = 0; i < len; i++) {
            char* temp = queue[outIndex++];
            if (strcmp(temp, endWord) == 0) {
                return cnt;
            }

            for (int j = 0; j < m; j++) {
                if (visited[j] == 0 && isMatch(temp, wordList[j])) {
                    visited[j] = 1;
                    queue[inIndex++] = wordList[j];
                }
            }
        }
        cnt++;
    }

    return 0;
}
```

#### [102. 二叉树的层序遍历](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)

```c
#define QUEUE_SIZE 100001

typedef struct {
    struct TreeNode* node;
    int level;
} myQueue;

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    if (root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    myQueue queue[QUEUE_SIZE];
    int cnt[QUEUE_SIZE] = {0};
    int levels = 0;
    int inIndex = -1;
    int outIndex = -1;

    myQueue* out = NULL;
    myQueue* in = &queue[++inIndex];

    in->node = root;
    in->level = 0;
    cnt[in->level] += 1;
    levels = in->level + 1;

    while (outIndex != inIndex) {
        out = &queue[++outIndex];

        if (out->node && out->node->left) {
            in = &queue[++inIndex];
            in->node = out->node->left;
            in->level = out->level + 1;
            cnt[in->level] += 1;
            levels =  in->level + 1;
        }
        if (out->node && out->node->right) {
            in = &queue[++inIndex];
            in->node = out->node->right;
            in->level = out->level + 1;
            cnt[in->level] += 1;
            levels =  in->level + 1;
        }
    }

    int **result = (int**)malloc(sizeof(int*) * (levels + 1));
    int *resultColSizes = (int*) malloc(sizeof(int) * (levels + 1));
    for (int i = 0; i < levels; i++) {
        result[i] = (int*)malloc(sizeof(int) * (cnt[i] + 1));
        resultColSizes[i] = cnt[i];
    }

    int k = -1;
    for (int i = 0; i < levels; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            result[i][j] = queue[++k].node->val;
        }
    }

    *returnColumnSizes = resultColSizes;
    *returnSize = levels;
    return result;
}
```

#### [429. N叉树的层序遍历](https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/)

```c
#define QUEUE_SIZE 100000

typedef struct {
    struct Node* node;
    int level;
} myQueue;

int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
    if (root == NULL) {
        *returnColumnSizes = NULL;
        *returnSize = 0;
        return NULL;
    }

    myQueue queue[QUEUE_SIZE];
    int cnt[QUEUE_SIZE] = {0};
    int levels = 0;
    int inIndex = -1;
    int outIndex = -1;

    myQueue* out = NULL;
    myQueue* in = &queue[++inIndex];

    in->node = root;
    in->level = 0; 
    cnt[in->level] += 1;
    levels = in->level + 1;

    while(outIndex < inIndex) {
        outIndex++;
        myQueue* temp = &queue[outIndex];
        if (temp->node->numChildren) {
            for (int i = 0; i < temp->node->numChildren; i++) {
                in = &queue[++inIndex];
                in->node = temp->node->children[i];
                in->level = temp->level + 1; 
                cnt[in->level] += 1;
                levels = in->level + 1;
            }
        }
    }

    int **result = (int**)malloc(sizeof(int*) * (levels + 1));
    int *resultColSizes = (int*) malloc(sizeof(int) * (levels + 1));
    for (int i = 0; i < levels; i++) {
        result[i] = (int*)malloc(sizeof(int) * (cnt[i] + 1));
        resultColSizes[i] = cnt[i];
    }

    inIndex = -1;
    for (int i = 0; i < levels; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            in = &queue[++inIndex];
            result[i][j] = in->node->val;
        }
    }

    *returnColumnSizes = resultColSizes;
    *returnSize = levels;
    return result;

}
```

## 贪心算法：

贪心算法总是作出在当前看来最好的选择。也就是说贪心算法并不从整体最优考虑，它所作出的选择只是在某种意义上的**局部最优**选择。当然，希望贪心算法得到的最终结果也是整体最优的。虽然贪心算法不能对所有问题都得到整体最优解，但对许多问题它能产生整体最优解。如**单源最短路经问题**，**最小生成树问题**等。在一些情况下，即使贪心算法不能得到整体最优解，其最终结果却是**最优解的很好近似**。

从许多可以用贪心算法求解的问题中看到这类问题一般具有2个重要的性质：**贪心选择性质**和**最优子结构性质**。

### 贪心选择性质

所谓贪心选择性质是指所求问题的整体最优解可以通过一系列局部最优的选择，即贪心选择来达到。这是贪心算法可行的第一个基本要素，也是贪心算法与动态规划算法的主要区别。

动态规划算法通常以自底向上的方式解各子问题，而贪心算法则通常以自顶向下的方式进行，以迭代的方式作出相继的贪心选择，每作一次贪心选择就将所求问题简化为规模更小的子问题。

对于一个具体问题，要确定它是否具有贪心选择性质，必须证明每一步所作的贪心选择最终导致问题的整体最优解。

### 最优子结构性质

当一个问题的最优解包含其子问题的最优解时，称此问题具有最优子结构性质。问题的最优子结构性质是该问题可用动态规划算法或贪心算法求解的关键特征。

贪心算法与动态规划算法的差异
贪心算法和动态规划算法都要求问题具有最优子结构性质，这是2类算法的一个共同点。但是，对于具有最优子结构的问题应该选用贪心算法还是动态规划算法求解?是否能用动态规划算法求解的问题也能用贪心算法求解?下面研究2个经典的组合优化问题，并以此说明贪心算法与动态规划算法的主要差别。

#### 例子1：0-1背包问题

给定n种物品和一个背包。物品i的重量是Wi，其价值为Vi，背包的容量为C。应如何选择装入背包的物品，使得装入背包中物品的总价值最大?

1 注：在选择装入背包的物品时，对每种物品i只有2种选择，即装入背包或不装入背包。不能将物品i装入背包多次，也不能只装入部分的物品i。

#### 例子2：背包问题

与0-1背包问题类似，所不同的是在选择物品i装入背包时，可以选择物品i的一部分，而不一定要全部装入背包，1≤i≤n。

这2类问题都具有最优子结构性质，极为相似，但**背包问题可以用贪心算法求解，而0-1背包问题却不能用贪心算法求解**。

用贪心算法解背包问题的基本步骤：

1首先计算每种物品单位重量的价值Vi/Wi，然后，依贪心选择策略，将尽可能多的单位重量价值最高的物品装入背包。
 2 若将这种物品全部装入背包后，背包内的物品总重量未超过C，则选择单位重量价值次高的物品并尽可能多地装入背包。
 3 依此策略一直地进行下去，直到背包装满为止。
具体算法可描述如下：

```java
public static float knapsack(float c,float [] w, float [] v,float [] x)
   {
      int n=v.length;
      Element [] d = new Element [n];
      for (int i = 0; i < n; i++) d[i] = new Element(w[i],v[i],i);
      MergeSort.mergeSort(d);
      int i;
      float opt=0;
      for (i=0;i<n;i++) x[i]=0;
      for (i=0;i<n;i++) {
        if (d[i].w>c) break;
        x[d[i].i]=1;
        opt+=d[i].v;
        c-=d[i].w;
        }
      if (i<n){
        x[d[i].i]=c/d[i].w;
        opt+=x[d[i].i]*d[i].v;
        }
      return opt;
   }
```

1 注：算法knapsack的主要计算时间在于将各种物品依其单位重量的价值从大到小排序。因此，算法的计算时间上界为O(nlogn）。
2 当然，为了证明算法的正确性，还必须证明背包问题具有贪心选择性质。
对于0-1背包问题，贪心选择之所以不能得到最优解是因为在这种情况下，它无法保证最终能将背包装满，部分闲置的背包空间使每公斤背包空间的价值降低了。事实上，在考虑0-1背包问题时，应比较选择该物品和不选择该物品所导致的最终方案，然后再作出最好选择。由此就导出许多互相重叠的子问题。这正是该问题可用动态规划算法求解的另一重要特征。
实际上也是如此，动态规划算法的确可以有效地解0-1背包问题。

### 贪心算法的基本步骤

为了形式化地描述贪心算法的一般处理过程，我们对所要求解的问题做如下假设。

1）有一个以优化方式来求解的问题。
为了构造问题的解决方案，有一个候选的对象的集合C，如活动安排问题中的活动集合E ={1,2,3，…，n}。

2）随着问题求解过程的进行，这个集合将逐步被划分为两个集合： 一个包含已经被考虑过并被选择的候选对象集合S；另一个包含已经被考虑过但被丢弃的候选对象。

3）有一个函数solution(S)来检查一个所选择的对象集合是否提供了问题的解答。该函数不考虑此时的解决方法是否最优。如活动安排问题中所有活动是否已经被考察。

4）还有一个函数feasible(S)检查是否一个所选对象的集合是可行的，也即是否可能往该集合上添加更多的候选对象以获得一个解。和上一个函数一样，此时不考虑解决方法的最优性。在活动安排问题中，这个函数用来判断所选出的活动之间是否相容。

5）选择函数select ©用来从剩余候选对象集合中，根据当前状态选择出最有希望问题最优解的对象。在在活动安排问题中，选择函数是从剩余活动中选择最早结束的活动。

6）最后，有一个目标函数给出问题解的值，如在活动安排问题中被选择安排的活动数。

其中，选择函数是贪心算法设计的关键，通常与目标函数有关。

### 代码模板：

```python
 function greedy(C) {  /*C是候选对象集合*/
	  S=Ф;  /*集合S是构造解*/
      while (C!= Ф && ! solution(S) ) {
		  x=select(C);
		  C=C-{x};
		  if ( feasible(S∪{x}) ) S= S∪{x};
      }
      if ( solution(S) ) return S;
      else return “No solutions”;
}
```

### 代码实践：

#### [860. 柠檬水找零](https://leetcode-cn.com/problems/lemonade-change/)

找零钱，针对20元，优先使用大面额的10元；

```c
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
```

#### [122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

只要第二天的价格比第一天的价格高，则买卖，计算收益；

```c
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
```

#### [455. 分发饼干](https://leetcode-cn.com/problems/assign-cookies/)

升序排序，顺序比较，满足即分配，计数加一；

```c
int cmp(const void *a, const void *b){
    if (*(int*)a > *(int*)b) {
        return 1;
    }
    return -1;
}

int findContentChildren(int* g, int gSize, int* s, int sSize){
    if (g == NULL || gSize <= 0 || s == NULL | sSize <= 0) {
        return 0;
    }

    qsort(g, gSize, sizeof(g[0]), cmp);
    qsort(s, sSize, sizeof(s[0]), cmp);

    int cnt = 0;
    int i = 0;
    int j = 0;
    while (i < gSize && j < sSize) {
        if (s[j] >= g[i]) {
            cnt++;
            i++;
        }
        j++;
    }

    return cnt;
}
```

#### [55. 跳跃游戏](https://leetcode-cn.com/problems/jump-game/)

在每个下标i可跳达的范围内，总是选择i + nums[i]为最远的；

```c
bool canJump(int* nums, int numsSize){
    if (nums == NULL | numsSize <= 0) {
        return true;
    }

    int end = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i <= end) {
            end = fmax(end, nums[i] + i);
        }
        if (end >= numsSize - 1) {
            return true;
        }
    }

    return false;
}
```

#### [45. 跳跃游戏 II](https://leetcode-cn.com/problems/jump-game-ii/)

在每个下标i可跳达的范围内，总是选择i + nums[i]为最远的为end，并且在达到end时，计数加一；

```c
int jump(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 1) {
        return 0;
    }

    int end = 0;
    int maxPos = 0;
    int result = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        maxPos = fmax(maxPos, nums[i] + i);
        if (i == end) {
            end = maxPos;
            result++;
        }
    }

    return result;
}
```

## 二分查找：

一种在有序数组中查找某一特定元素的搜索算法。

搜索过程从数组的中间元素开始，如果中间元素正好是要查找的元素，则搜索过程结束；

如果某一特定元素大于或者小于中间元素，则在数组大于或小于中间元素的那一半中查找，而且跟开始一样从中间元素开始比较。如果在某一步骤数组为空，则代表找不到。

这种搜索算法每一次比较都使搜索范围缩小一半。

二分查找代码出错原因主要集中在判定条件和边界值的选择上，很容易就会导致越界或者死循环的情况。几个要注意的点：

1 循环的判定条件是：`low <= high`

2 为了防止数值溢出，`mid = low + (high - low)/2`

3 当 `A[mid]`不等于`target`时，`high = mid - 1`或`low = mid + 1`

### 代码模板：

```java
left, right = 0, len(array) - 1 
while left <= right: 
	  mid = (left + right) / 2 
	  if array[mid] == target: 
		    # find the target!! 
		    break or return result 
	  elif array[mid] < target: 
		    left = mid + 1 
	  else: 
		    right = mid - 1
```

### 代码实践：

#### [33. 搜索旋转排序数组](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

比较特殊，非全排序场景，比较时需要加上头尾节点的值;

```c
int search(int* nums, int numsSize, int target){
    if (nums == NULL || numsSize <= 0) {
        return -1;
    }

    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[0] <= nums[mid]) {
            if (nums[0] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;  
            }
        } else {
            if (nums[mid] < target && target <= nums[numsSize - 1]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } 
    }

    return -1;
}
```

#### [74. 搜索二维矩阵](https://leetcode-cn.com/problems/search-a-2d-matrix/)

特殊的一点是多组升序序列里查找目标值，每行优先比较尾节点最大值与目标值的大小关系；

```c
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target){
    if (matrixSize <= 0 || matrixColSize[0] <= 0) {
        return false;
    }

    int row = 0;
    int col = matrixColSize[0] - 1;
    while (row < matrixSize) {
        if (target > matrix[row][col]) {
            row++;
        } else if (target == matrix[row][col]) {
            return true;
        } else {
            int left = 0;
            int right = col;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (target == matrix[row][mid]) {
                    return true;
                }
                if (target > matrix[row][mid]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return false;
        }
    }

    return false;
}
```

#### [153. 寻找旋转排序数组中的最小值](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)

寻找旋转排序数组中的最小值，将mid和right尾节点比较：

1 如果mid比right大，也即mid和right之间包含半有序数组中的无序部分，意味着比最小值一定在mid + 1和right之间；

2 如果mid比right小，也即mid和right之间为全升序序列，反过来意味着left和mid之间包含半有序数组中的无序部分，最小值一定在left和mid 之间，注意此处是包含mid的，将mid置为right；

3 最终查找的left即为数组中最小值，而left - 1也即数组中的最大值；也即半有序数组中间无序的地方为查找的left - 1， left；

```c
int findMin(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 0) {
        return -1;
    }

    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    //printf("max = %d, min = %d\n", nums[left - 1], nums[left]);

    return nums[left];
}
```
