# 学习笔记

重点学习哈希表，进行2道相关题目的练习，分别总结下，练习过程中的问题；由于leetcode针对C语言集成了uthash.h，也就考虑基于uthash来实现;

## [两数之和](https://leetcode-cn.com/problems/two-sum/)

第一种算法：1）数组排序；2）使用left、right双指针的方法来寻找和为target的对应元素的下标;

第二种算法：1）将数组的元素值作为key，元素下标作为值加入哈希表；2）遍历数组，在哈希表中查询key = target - nums[i]的； 

基于哈希表的方法实现，主要碰到如下的两个问题：

1）有可能存在nums[i] == target - nums[i]，也就是通过target - nums[i]查询得到的还是num[i]的下标；

2）有可能存在两个元素的值是相同的，也即nums[i] == nums[j]，添加到哈希表对应的是同一个key；

### **Hash数据结构定义：**

typedef struct hash_entry {

​    int key;

​    int val[2];    *//此处val字段是记录元素的下表，数组 size为2，也即假定可能存在2个相同值的元素；* 

​    UT_hash_handle hh;

} entry;

### **添加HASH表的特殊处理：**

bool AddHash(entry** hashMap, int k, int i){

​    entry* ret = NULL;

​    HASH_FIND_INT(*hashMap, &k, ret);

​    if (ret == NULL) {  *// 代表首次加入key*

​        entry* p = (entry*)malloc(sizeof(entry));   

​        p->key = k;

​        p->val[0] = i;    *// 代表首次加入key的元素下标*；

​        p->val[1] = -1;   *// 置为-1，表示没有相同值的另一个元素；*

​        HASH_ADD_INT(*hashMap, key, p);

​        return true;

​    } else { *// 代表第二次加入相同的key*

​        ret->val[1] = i;  *// 置为另一个元素的下标；*

​        return true;

​    }     

}

### **遍历数组，查哈希表匹配的处理**

for (int i = 0; i < numsSize; i++) {

​        index1 = i;

​        entry* find = FindHash(&hashMap, target - nums[i]);

​        if (find) {

​            if (find->val[0] == i) {  *//判断找到是否是nums[i]本身*

​                if (find->val[1] == -1) {  *//如果是nums[i]，再判断是否存在相同值的另一个元素*

​                    continue;

​                } 

​                index2 = find->val[1]; //如果存在另一个元素，则取下标值；

​            } else {

​                index2 = find->val[0];

​            }

​            flag = 1;

​            break;

​        }

​    }



## [字母异位词分组](https://leetcode-cn.com/problems/group-anagrams/)

直接考虑采用哈希表的方法：1）复制一份字符串数组，对每个字符串进行排序；2）将排序的字符串作为key，下标作为val添加到hash表；

主要考虑要解决的问题是，可能会有多个字符串的key是相同的，因此同一key下需要记录多个下标；

### **Hash数据结构定义：**

typedef struct hash_entry {

​    char key[30];  //字符串作为key；

​    int val[20];   //val数组，支持记录多个下标；

​    int cnt;  //记录的下标数

​    UT_hash_handle hh;

} entry;

### **添加HASH表的特殊处理：**

bool AddHash(entry** hashMap, char *key, int i){

​    entry* ret = NULL;

​    HASH_FIND_STR(*hashMap, key, ret);

​    if (ret == NULL) { *// 代表首次加入key*

​        entry* p = (entry*)malloc(sizeof(entry));

​        strcpy(p->key, key);

​        p->val[0] = i; *// 代表首次加入key的元素下标*；

​        p->cnt = 1; *// 下标计数为1*；

​        HASH_ADD_STR(*hashMap, key, p);

​        return true;

​    } else { *// 代表第一次后续加入相同的key*

​        ret->val[ret->cnt] = i;  *// 代表后续加入key的元素下标*；

​        ret->cnt++; *// 下标计数加1*；

​        return true;

​    }

}

