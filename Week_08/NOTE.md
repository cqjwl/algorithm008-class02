# 学习笔记

## 冒泡排序：

冒泡排序：不断比较相邻的两个数，让较大的元素不断地往后移。经过一轮比较，就选出最大的数；经过第2轮比较，就选出次大的数，以此类推；

复杂度：时间复杂度最坏为O(n2)，平均为O(n2)，空间复杂度O(1)；  

### 代码实践：

```c
void swap(int* a, int* b){
    int tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;
}

void bubble_sort(int* nums, int numsSize){
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = numsSize - 2; j >= i; j--) {
            if(nums[j] > nums[j + 1]) {
                swap(&nums[j], &nums[j + 1]);
            }
        }
    }
}
```

## 快速排序：

快速排序：使用分治法（Divide and conquer）策略，将所要进行排序的数分为左右两个部分，其中一部分的所有数据都比另外一 部分的数据小，然后将所分得的两部分数据进行同样的划分，递归地执行以上的划分操作，直 到所有要进行排序的数据变为有序为止；算法步骤：

从数列中挑出一个元素，称为 “基准”（pivot）。

重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作。

递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序。

递归的最底部情形，是数列的大小是零或一，也就是永远都已经被排序好了。虽然一直递归下去，但是这个算法总会退出，因为在每次的迭代（iteration）中，至少会把一个元素摆到最后的位置去；

### 代码实践：

```c
void swap(int* a, int* b){
    int tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;
}

int partition(int* nums, int low, int high){
    //基准元素
    int pivotLKey = nums[low];
    //从表的两端交替地向中间扫描
    while (low < high){
        while (low < high && nums[high] >= pivotLKey) { 
            high--;
        }
        swap(&nums[low], &nums[high]);
        
        while (low < high && nums[low] <= pivotLKey) {
            low++;
        }
        swap(&nums[low], &nums[high]);
    }
    return low;
}

void quick_sort(int* nums, int low, int high){
    if (low < high){
        //将表一分为二
        int pivotPos = partition(nums, low, high);
        //对低子表递归排序
        quick_sort(nums, low, pivotPos - 1);
        //对高子表递归排序
        quick_sort(nums, pivotPos + 1, high);
    }
    
    return;
}
```

## 直接插入排序：

直接插入排序：将数组中的所有元素依次跟前面已经排好的元素相比较，如果选择的元素比已排序的元素小，则交换，直到全部元素都比较过 因此，直接插入排序可以用两个循环完成：

第一层循环：遍历待比较的所有数组元素

第二层循环：将本轮选择的元素(selected)与已经排好序的元素(ordered)相比较。如果：selected > ordered，那么将二者交换。

复杂度：时间复杂度最坏为O(n2)，平均为O(n2)，空间复杂度O(1)；

### 代码实践：

```c
void insert_sort(int* nums, int numsSize){
    for (int i = 1; i < numsSize;i++) {
        if (nums[i] < nums[i - 1]) {
            int j = i - 1;
            //复制为哨兵，即保存为待排序元素
            int tmp = nums[i];
            //先后移一个元素
            nums[i] = nums[i - 1];
            //查找在有序表的插入位置
            while (tmp < nums[j]) {
                //元素后移
                nums[j + 1] = nums[j];
                j--;
            }
            //插入到正确的位置
            nums[j + 1] = tmp;
        }
    }
}
```

## 希尔排序：

希尔排序：也称递减增量排序算法，是插入排序的一种更高效的改进版本。但希尔排序是非稳定排序算法。

希尔排序的基本思想是：先将整个待排序的记录序列分割成为若干子序列（由相隔某个“增量”的元素组成的）分别进行直接插入排序，，然后依次缩减增量再进行排序，待整个序列中的元素基本有序（增量足够小）时，再对全体元素进行一次直接插入排序。

复杂度：希尔排序的时间复杂度取决于所采用的增量序列，典型的增量序列是shell增量序列和Hibbard增量序列，时间复杂度分别是O(n2)和O(n3/2)（3/2表示二分之三次方）；空间复杂度为O(1)。

算法步骤：

1. 选择一个增量序列t1，t2，…，tk，其中ti>tj，tk=1；

2. 按增量序列个数k，对序列进行k 趟排序；

3. 每趟排序，根据对应的增量ti，将待排序列分割成若干长度为m 的子序列，分别对各子表进行直接插入排序。仅增量因子为1 时，整个序列作为一个表来处理，表长度即为整个序列的长度。

### 代码实践：

```c
void shell_insert_sort(int* nums, int numsSize, int dk){
    for (int i = dk; i < numsSize;i++) {
        if (nums[i] < nums[i - dk]) {
            int j = i - dk;
            //复制为哨兵，即保存为待排序元素
            int tmp = nums[i];
            //先后移一个元素
            nums[i] = nums[i - 1];
            //查找在有序表的插入位置
            while (tmp < nums[j]) {
                //元素后移
                nums[j + dk] = nums[j];
                j -= dk;
            }
            //插入到正确的位置
            nums[j + dk] = tmp;
        }
    }
}

void shell_sort(int* nums, int numsSize){
    int dk = numsSize / 2;
    while (dk >= 1) {
        shell_insert_sort(nums, numsSize, dk);
        dk = dk / 2;
    }
}
```

## 简单选择排序：

选择排序：与冒泡法一致，还定义了记号k=i，然后依次把a[k]同后面元素比较，若a[k]>a[j]，则使k=j；最后看看k=i是否还成立，不成立则交换a[k]，a[i]，这样就比冒泡法省下许多无用的交换，提高了效率；可通过两层循环实现：

第一层循环：依次遍历序列当中的每一个元素；

第二层循环：将遍历得到的当前元素依次与余下的元素进行比较，符合最小元素的条件，则交换。

复杂度：时间复杂度最坏为O(n2)，平均为O(n2)，空间复杂度为O(1)；

### 代码实践：

```c
void swap(int* a, int* b){
    int tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;
}

void  selset_sort(int* nums, int numsSize){
    int i,j,k,tmp;   
    for (i = 0; i < numsSize - 1; i++) {
        //给记号k赋值
        k = i;    
        for (j = i + 1; j < numsSize; j++)   
            if (nums[k] > nums[j]) {
                //是k总是指向最小元素
                k = j; 
            }
            //当k!=i时，才交换，否则a[i]即为最小
            if (i != k) {   
                swap(&nums[i], &nums[k]);
            }
        }
    }
}
```

## 堆排序：

堆排序：通过将无序表转化为堆，可以直接找到表中最大值或者最小值，然后将其提取出来，令剩余的记录再重建一个堆，取出次大值或者次小值，如此反复执行就可以得到一个有序序列，此过程为堆排序；

### 代码实践：

```c
void swap(int* a, int* b){
    int tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;
}

void max_heapify(int *nums, int start, int end) 
{
    //建立父节点下标和子节点下标
    int dad = start;
    int son = dad * 2 + 1;

    while (son <= end){
        //若子节点下标在范围内才做比较
        //先比较两个子节点大小，选择最大的
        if (son + 1 <= end && nums[son] < nums[son + 1]){
            son++;
        }
        
        //如果父节点大于子节点代表调整完毕,直接跳出
        if (nums[dad] > nums[son]) {
            return;
        } else {   
            //否则交换父子节点的值再继续左右子节点值得比较
            swap(&nums[dad], &nums[son]);
            dad = son;
            son = dad * 2 + 1;
        }  
    }
}

void heap_sort(int *nums, int len) 
{
    int i;
    //初始化，i从最后一个父节点开始调整
    for (i = len / 2 - 1; i >= 0; i--) {
        max_heapify(nums, i, len - 1);
    }

    for (i = len - 1; i > 0; i--) {
        swap(&nums[0], &nums[i]);
        max_heapify(nums, 0, i - 1);
    }
}
```

## 归并排序：

归并排序：建立在归并操作上的一种有效的排序算法。该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。

复杂度：时间复杂度最坏为O(n*logn)，平均为O(n*logn)，空间复杂度为O(n)。

算法步骤：

1. 申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列；

2. 设定两个指针，最初位置分别为两个已经排序序列的起始位置；

3. 比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置；

4. 重复步骤3直到某一指针达到序列尾；

5. 将另一序列剩下的所有元素直接复制到合并序列尾；

### 代码实践：

```c
void merge(int* r, int* rf, int i, int m, int n){
    int j, k;
    for (j = m + 1, k = i; i <= m && j <= n; ++k) {
        if (r[j] < r[i]) {
            rf[k] = r[j++];
        } else {
            rf[k] = r[i++];
        }
    }
    
    while (i <= m) {
        rf[k++] = r[i++];
    }
    
    while (j <= n) {
        rf[k++] = r[j++];
    }
}

void merge_sort(int* r, int* rf, int rSize) 
{
    int len = 1;
    int* q = r;
    int* tmp;
    while (len < rSize) {
        int s = len;
        len = 2 * s;
        while (i + len < rSize) {
            //对等长的两个子表合并
            merge(q, rf, i, i + s - 1, i + len - 1);
        }
        
        if (i + s < rSize) {
            //对不等长的两个子表合并
            merge(q, rf, i, i + s - 1, rSize - 1); 
        }
        //交换q, rf，以保证下一次归并时，仍从q归并到rf
        tmp = q;
        q = rf;
        rf = tmp;
    }
}
```

## 基数排序：

基数排序：通过序列中各个元素的值，对排序的N个元素进行若干趟的“分配”与“收集”来实现排序。

**分配**：将L[i]中的元素取出，首先确定其个位上的数字，根据该数字分配到与之序号相同的桶中 。

**收集**：当序列中所有的元素都分配到对应的桶中，再按照顺序依次将桶中的元素收集形成新的一个待排序列L[ ] 。

对新形成的序列L[]重复执行分配和收集元素中的十位、百位...直到分配完该序列中的最高位，则排序结束。

将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序完成以后，数列就变成一个有序序列。

基数排序按照优先从高位或低位来排序有两种实现方案：

**MSD（Most significant digital）** 从最左侧高位开始进行排序。先按k1排序分组, 同一组中记录, 关键码k1相等,再对各组按k2排序分成子组, 之后, 对后面的关键码继续这样的排序分组, 直到按最次位关键码kd对各子组排序后. 再将各组连接起来,便得到一个有序序列。MSD方式适用于位数多的序列。
**LSD （Least significant digital）**从最右侧低位开始进行排序。先从kd开始排序，再对kd-1进行排序，依次重复，直到对k1排序后便得到一个有序序列。LSD方式适用于位数少的序列。

复杂度：时间复杂度为O(d(n+r))，空间复杂度为O(r)，d为位数，r为基数，稳定。

### 代码实践：

```c
//求数字位数
int bit_num(int num){
    if (num / 10 == 0){
        return 1;
    }
    return 1 + bit_num(num/10);
}
 
//求序列最大值
int max_list(int* nums, int numsSize){
    int max_num = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > max_num) {
            max_num = nums[i];
        }
    }
    return max_num;
}
 
//找到一个num从低位到高位的第pos位的数据，数据最右侧最低位pos=1
int get_num_pos(int num, int pos){
    if (pos <= 0) {
        return -1;
    };
    
    int pow_num = 1;
    for(int i = 0; i < pos - 1; i++) {
        pow_num *= 10;
    } 
    
    return (num / pow_num) % 10;    
}
 
//基数排序
void base_sort(int* nums, int numsSize){
    int max_num, key_num;
    //十进制的10个桶
    int *base_nums[10];
    max_num = max_list(arr,length);  
   
    key_num = bit_num(max_num);
   
    for (int i = 0; i < 10; i++) {
        base_nums[i] = (int*)malloc(sizeof(int) * (numsSize + 1));
        //桶中第一个位置记录桶中元素的数量
        base_nums[i][0] = 0;
    }
    
    //需要执行最大位数次
    for (int pos = 1; pos <= key_num; pos++) { 
        for (int i = 0; i < numsSize; i++) {
            int num = get_num_pos(nums[i], pos);
            int index = ++base_nums[num][0];
            base_nums[num][index] = nums[i];
        }
        
        for (int i = 0, j = 0; i < 10; i++) {
            for (int k = 1; k <= base_nums[i][0]; k++){
                arr[j++] = base_nums[i][k];
            }
            base_nums[i][0]=0;
        }
    }
}
```

## 计数排序：

计数排序：假定待排序的所有元素都是介于0到K之间的整数；计数排序使用一个额外的数组countArray，其中第i个元素是待排序数组array中值等于i的元素的个数。然后根据数组countArray来将array中的元素排到正确的位置。

算法的步骤如下：

找出待排序的数组中最大和最小的元素
统计数组中每个值为i的元素出现的次数，存入数组countArray的第i项
对所有的计数累加（从countArray中的第一个元素开始，每一项和前一项相加）
反向填充目标数组：将每个元素i放在新数组的第countArray[i]项，每放一个元素就将countArray[i]减去1
复杂度：平均时间复杂度、最优时间复杂度和最差时间复杂度都为O(n+k)，空间复杂度为O(n+k)，其中，n为待排元素个数，k为待排元素的范围(0~k)。

### 代码实践：

```c
#define RANDMAX 1000000
#define RANDMIN 900000

//利用伪随机数填充数组array，伪随机数的范围在RANDMIN~RANDMAX-1之间
void get_randNums(int* nums, int numsSize)
{
    srand((unsigned) time(NULL));
    int i = 0;
    for (i = 0; i < numsSize; ++i) {
        nums[i] = rand() % (RANDMAX - RANDMIN) + RANDMIN ;
    }
}
 
//从小到大进行排序
void count_sort(int* nums, int numsSize)
{
    //计数数组，用于统计数组nums中各个不同数出现的次数
    //由于数组nums中的数属于0...RANDMAX-1之间，所以countArray的大小要够容纳RANDMAX个int型的值
    int* countNums = (int*) calloc(RANDMAX, sizeof(int));
    //用于存放已经有序的数列
    int* sortedNums = (int*) calloc(size, sizeof(int));
 
    //统计数组nums中各个不同数出现的次数，循环结束后countNums[i]表示数值i在nums中出现的次数
    int index = 0;
    for (index = 0; index < size; ++index) {
        countNums[nums[index]]++;
    }
 
    //统计数值比index小的数的个数，循环结束之后countNums[i]表示nums中小于等于数值i的元素个数
    for (index = 1; index < RANDMAX; ++index) {
        countNums[index] += countNums[index - 1];
    }
 
    for (index = size - 1; index >= 0; --index) {
        //因为数组的起始下标为0，所以要减一
        sortedNums[countNums[nums[index]] - 1] = nums[index];
        //这里减一是为了保证当有多个值为nums[index]的元素时，后出现的值为nums[index]的元素
        //放在后面，也就是为了保证排序的稳定性
        --countNums[nums[index]];
    }
 
    memcpy(nums, sortedNums, sizeof(int) * numsSize);
    free(sortedNums);
    free(countNums);
}
```

## 桶排序：

桶排序：计数排序的升级版。利用了函数的映射关系，高效与否的关键就在于这个映射函数的确定；工作的原理：假设输入数据服从均匀分布，将数据分到有限数量的桶里，每个桶再分别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行）。

算法的步骤如下：

设置一个定量的数组当作空桶；
遍历输入数据，并且把数据一个一个放到对应的桶里去；
对每个不是空的桶进行排序；
从不是空的桶里把排好序的数据拼接起来。
复杂度：时间复杂度O(n+k)，空间复杂度O(n+k)。

### 代码实践：

```c
//求数组的最大值
int get_max(int* nums, int numsSize){
    int max = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[max]) {
            max = i;
        }
    }
    return nums[max];
}

// 建立一个MAX大小的数组，原数组的值作当前数组的下标
void bucket_sort(int* nums, int numsSize){
    int max = get_max(nums, numsSize);
    //空桶初始化
    int buckets[max + 1];
    memset(buckets, 0, sizeof(int) * (max + 1));
    
    int i = 0;
    int j = 0;
    //遍历序列，并且把元素一个一个放到对应的桶子去。
    for (i = 0; i < numsSize; i++) {
        buckets[nums[i++]]++;
    }
    
    for (i = 0, j = 0; i < max; ++i) {
        //对每个不是空的桶子进行排序
        while(buckets[i]) {
            //从不是空的桶子里把元素再放回原来的序列中
            nums[j] = i;
            j++;
            buckets[i]--;
        }
    }
}
```





































