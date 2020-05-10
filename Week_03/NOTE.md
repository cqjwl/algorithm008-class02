# 学习笔记

## 泛型递归：

### 代码模板：

```python
 def recursion(level, p1, p2, ...):
        
        # recursion terminator  
        if level > MAX_LEVEL:
            print(result)
            return 
        
        # process logic in current level
        p1_pro, p2_pro = process_data(level, data...)
        
        # drill down
        self.recursion(level + 1, p1_pro, p2_pro, ...)
        
        # reverse the current level stattus if needed
        reverse_state(level)
```

### 代码实践：

#### [第 N 个泰波那契数](https://leetcode-cn.com/problems/n-th-tribonacci-number/)

第1解法：存在重复计算，造成超时；

```c
int tribonacci(int n){
    if (n == 0) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    //重复递归计算(n - x)
    return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
}
```

第2解法：尾递归，保存中间计算结果；

```c
int tribonacci(int n, int dp1, int dp2, int dp3){
    if (n == 0) {
        return dp1;
    }
    if (n == 1) {
        return dp2;
    }
    if (n == 2) {
        return dp3;
    }
    
    return tribonacci(n - 1) , dp2, dp3, dp3 + dp2 + dp1);
}
```

第3解法：非递归，动态规划；

```c
int tribonacci(int n){
    if (n == 0) {
        return 0;
    }

    if (n == 1 || n == 2) {
        return 1;
    }

    int dp[3];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;

    for (int i = 3; i <= n; i++) {
        int temp = dp[0] + dp[1] + dp[2];
        dp[0] = dp[1];
        dp[1] = dp[2];
        dp[2] = temp;
    }

    return dp[2];
}
```

## 树的递归：

### 代码模板：

```java
private void helper(TreeNode node, String preStr, List<String> result) {

        // terminator
        if (node == null) return;

        // process
        preStr += node.val;
        if (node.left == null && node.right == null) {
            result.add(preStr);
            return;
        }

        // drill down
        if (node.left != null) helper(node.left, preStr, result);
        if (node.right != null) helper(node.right, preStr, result);

        // clear state
    }
```

### 代码实践：

#### [面试题 17.12. BiNode](https://leetcode-cn.com/problems/binode-lcci/)

```c
void helper(struct TreeNode* root, struct TreeNode** head, struct TreeNode** prev){
    if (root == NULL) {
        return;
    }

    helper(root->left, head, prev);
    if (root) {
        if (head[0] == NULL) {
            head[0] = root;
            head[0]->left = NULL;
            prev[0] = head[0];
        } else {
            prev[0]->right = root;
            prev[0] = prev[0]->right;
            prev[0]->left = NULL; 
        }
    }
    helper(root->right, head, prev);
    
    return;
}

struct TreeNode* convertBiNode(struct TreeNode* root){
    struct TreeNode* head = NULL;
    struct TreeNode* prev = NULL;
    helper(root, &head, &prev);
    return head;
}
```

#### [938. 二叉搜索树的范围和](https://leetcode-cn.com/problems/range-sum-of-bst/)

```c
void helper(struct TreeNode* root, int L, int R, int *result) {
    if (root == NULL) {
        return;
    }

    if (L <= root->val && root->val <= R) {
        result[0] += root->val;
    }
    
    if (L < root->val) {
        helper(root->left, L, R, result);
    }
    if (root->val < R) {
        helper(root->right, L, R, result);
    }
    
    return;
}

int rangeSumBST(struct TreeNode* root, int L, int R){
    if (root == NULL) {
        return 0;
    }

    int result = 0;
    helper(root, L, R, &result);
    
    return result;
}
```

#### [面试题68 - II. 二叉树的最近公共祖先](https://leetcode-cn.com/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof/)

```c
bool helper(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q, struct TreeNode** result) {
    if (root == NULL) {
        return false;
    }

    int cnt = 0;
    if (helper(root->left, p, q, result)) {
        cnt++;
    }
    if (helper(root->right, p, q, result)) {
        cnt++;
    }
    if (root == p || root == q) {
        cnt++;
    }

    if (cnt >= 2) {
        result[0] = root;
    }
    if (cnt > 0) {
        return true;
    }
    return false;
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q){
    struct TreeNode* result = NULL;
    helper(root, p, q, &result);
    return result;
}
```

## 分治：

### 代码模板：

```python
 def divide_conquer(problem, param1, param2, ...):

        # recursion terminator
        if problem is None:
            print(result)
            return

        # prepare data
        data = prepare_data_and_para(problem)
        subproblems = split_problem(problem, data)
        
        # conquer subproblems
        subresult1 = self.divide_conquer(subproblems[0], p1, p2, ...)
        subresult2 = self.divide_conquer(subproblems[1], p1, p2, ...)
        subresult3 = self.divide_conquer(subproblems[2], p1, p2, ...)
        
        # process and generate the final result
        result = process_result(subresult1, subresult2, subresult3, ...)
```

### 代码实践：

#### [215. 数组中的第K个最大元素](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)

```c
int quick_sort(int* nums, int left, int right) {
    if (left <= right) {
        int i = left;
        int j = right;
        int x = nums[left];
        while (i < j) {
            while (i < j && nums[j] < x) {
                j--;
            }
            if(i < j) {
                nums[i++] = nums[j];
            }

            while(i < j && nums[i] > x) {
                i++;
            }
            if(i < j) {
                nums[j--] = nums[i];
            }
        }

        nums[i] = x;
        return i;
    }
    else {
        return -1;
    }
}

int findKthLargest(int* nums, int numsSize, int k){
    int left = 0;
    int right = numsSize - 1;

    while(true) {
        int res = quick_sort(nums, left, right);
        if(res == k - 1) {
            return nums[res];
        }
        if(res < k - 1) {
            left = res + 1;
        }
        if(res > k - 1) {
            right = res - 1;
        }
    }
}
```

## 回溯：

解决一个回溯问题，实际上就是一个决策树的遍历过程。你只需要思考 3 个问题：

1、路径：也就是已经做出的选择。

2、选择列表：也就是你当前可以做的选择。

3、结束条件：也就是到达决策树底层，无法再做选择的条件。

代码方面，回溯算法的框架：

```python
result = []
def backtrack(路径, 选择列表):
    if 满足结束条件:
        result.add(路径)
        return
for 选择 in 选择列表:
    做选择
    backtrack(路径, 选择列表)
    撤销选择
```

其核心就是 for 循环里面的递归，在递归调用之前「做选择」，在递归调用之后「撤销选择」，特别简单。

### 代码模板：

```java
private void backtrack(List<List<Integer>> list, List<Integer> tempList, int [] nums){
        //一个终结条件，也就是满足条件的时候
        if(tempList.size() == nums.length){
            //全局变量添加一个满足条件的集合
            list.add(new ArrayList<>(tempList));
        } else{
            for(int i = 0; i < nums.length; i++){
                if(tempList.contains(nums[i])) continue;
                //如果tempList没有包含nums[i]才添加
                tempList.add(nums[i]);
                //递归调用，此时的tempList一直在变化，直到满足终结条件才结束
                backtrack(list, tempList, nums);
                System.out.println("tempList的内容:"+tempList+"-------"+"i的值:"+i);
                //它移除tempList最后一个元素的作用就是返回上一次调用时的数据，也就是希望返回之前的节点再去重新搜索满足条件。这样才能实现回溯
                tempList.remove(tempList.size() - 1);
            }
        }
    }
```

### 代码实践：

#### [77. 组合](https://leetcode-cn.com/problems/combinations/)

```c
void backtrack(int n, int k, int start, int* stack, int *top, int** result, int* resultSize, int *resultColSize){
    if (top[0] == k - 1) {
        int *temp = (int*)malloc(sizeof(int) * k);
        memset(temp, 0, sizeof(int) * k);
        for (int i = 0; i <= top[0]; i++){
            temp[i] = stack[i];
        }

        result[resultSize[0]] = temp;
        resultColSize[resultSize[0]] = k;
        resultSize[0]++;
        return;
    }

    for (int i = start; i <= n; i++) {
        stack[++top[0]] = i;
        backtrack(n, k, i + 1, stack, top, result, resultSize, resultColSize);
        top[0]--;
    }

    return;
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes){
    if (n == 0 || k <= 0) {
        returnSize[0] = 0;
        *returnColumnSizes = NULL;
        return NULL;
    } 

    int stack[10000];
    int top = -1;
    memset(stack, 0, sizeof(int) * 10000);

    int **result = (int**)malloc(sizeof(int) * 10000);
    int resultSize = 0;
    int *resultColSize = (int*)malloc(sizeof(int) * 10000);

    int start = 1;
    backtrack(n, k, start, stack, &top, result, &resultSize, resultColSize);

    *returnColumnSizes = resultColSize;
    returnSize[0] = resultSize;
    return result;
}
```

#### [46. 全排列](https://leetcode-cn.com/problems/permutations/)

```c
void backtrack(int* used, int start, int* stack, int* nums, int numsSize, int** result, int* resultSize, int *resultColSize){
    if (start == numsSize) {
        int *temp = (int*)malloc(sizeof(int) * numsSize);
        memset(temp, 0, sizeof(int) * numsSize);
        for (int i = 0; i < numsSize; i++){
            temp[i] = stack[i];
        }

        result[resultSize[0]] = temp;
        resultColSize[resultSize[0]] = numsSize;
        resultSize[0]++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (used[i] == 0) {
            stack[start] = nums[i];
            used[i] = 1;
            backtrack(used, start + 1, stack, nums, numsSize, result, resultSize, resultColSize);
            used[i] = 0;
        }
    }

    return;
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int **result = NULL;
    if (nums == NULL || numsSize <= 0) {
        returnSize[0] = 0;
        *returnColumnSizes = NULL;
        return result;
    }

    int used[numsSize];
    memset(used, 0, sizeof(int) * numsSize);
    int start = 0;
    int stack[10000];
    memset(stack, 0, sizeof(int) * 10000);

    result = (int**)malloc(sizeof(int) * 10000);
    int resultSize = 0;
    int *resultColSize = (int*)malloc(sizeof(int) * 10000);

    backtrack(used, start, stack, nums, numsSize, result, &resultSize, resultColSize);

    *returnColumnSizes = resultColSize;
    returnSize[0] = resultSize;
    return result;
}
```

#### [47. 全排列 II](https://leetcode-cn.com/problems/permutations-ii/)

```c
int cmp(const void *a, const void *b){
    if (*(int*)a > *(int*)b) {
        return 1;
    }
    return -1;
}

void backtrack(int* used, int start, int* stack, int* nums, int numsSize, int** result, int* resultSize, int *resultColSize){
    if (start == numsSize) {
        int *temp = (int*)malloc(sizeof(int) * numsSize);
        memset(temp, 0, sizeof(int) * numsSize);
        for (int i = 0; i < numsSize; i++){
            temp[i] = stack[i];
        }
        result[resultSize[0]] = temp;
        resultColSize[resultSize[0]] = numsSize;
        resultSize[0]++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (used[i] || (i > 0 && !used[i - 1] && nums[i] == nums[i - 1])) {
            continue;
        }
        stack[start] = nums[i];
        used[i] = 1;
        backtrack(used, start + 1, stack, nums, numsSize, result, resultSize, resultColSize);
        used[i] = 0;
    }

    return;
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int **result = NULL;
    if (nums == NULL || numsSize <= 0) {
        returnSize[0] = 0;
        *returnColumnSizes = NULL;
        return result;
    }

    qsort(nums, numsSize, sizeof(nums[0]), cmp);

    int used[numsSize];
    memset(used, 0, sizeof(int) * numsSize);
    int start = 0;
    int stack[10000];
    memset(stack, 0, sizeof(int) * 10000);

    result = (int**)malloc(sizeof(int) * 10000);
    int resultSize = 0;
    int *resultColSize = (int*)malloc(sizeof(int) * 10000);

    backtrack(used, start, stack, nums, numsSize, result, &resultSize, resultColSize);

    *returnColumnSizes = resultColSize;
    returnSize[0] = resultSize;
    return result;
}
```

#### 