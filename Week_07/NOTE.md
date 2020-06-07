# 学习笔记

## 字典树：

字典树，又称 Trie 树，利用字符串之间的公共前缀，将重复的前缀合并在一起；

字典树的特点：
1、根节点不包含字符，除根节点外每一个节点都只包含一个字符； 

2、从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串； 

3、每个节点的所有子节点包含的字符都不相同；

时间复杂度：（单词搜索II的时间复杂度同理；）
假设所有字符串长度之和为n，构建字典树的时间复杂度为O(n)；
假设要查找的字符串长度为k，查找的时间复杂度为O(k)；

空间复杂度：
字典树每个节点都需要用一个数组来存储子节点的指针，即便实际只有两三个子节点，但依然需要一个完整大小的数组。所以，字典树比较耗内存，空间复杂度较高。

### 代码模板：

```c
class Trie {
    struct TrieNode {
        map<char, TrieNode*>child_table;
        int end;
        TrieNode(): end(0) {}
    };
        
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *curr = root;
        for (int i = 0; i < word.size(); i++) {
            if (curr->child_table.count(word[i]) == 0)
                curr->child_table[word[i]] = new TrieNode();
                
            curr = curr->child_table[word[i]];                
        }
        curr->end = 1;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        return find(word, 1);
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return find(prefix, 0);
    }
private:
    TrieNode* root;
    bool find(string s, int exact_match) {
        TrieNode *curr = root;
        for (int i = 0; i < s.size(); i++) {
            if (curr->child_table.count(s[i]) == 0)
                return false;
            else
                curr = curr->child_table[s[i]];
        }
        
        if (exact_match)
            return (curr->end) ? true : false;
        else
            return true;
    }
};
```

### 代码实践：

#### [208. 实现 Trie (前缀树)](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)



```c
#define CHILD_SIZE 26

typedef struct Trie{
    char data;
    struct Trie* child[CHILD_SIZE];
    int end;
} Trie;

/** Initialize your data structure here. */
Trie* trieCreate() {
    Trie *obj = malloc(sizeof(*obj));
    obj->data = '/';

    for (int i = 0; i < CHILD_SIZE; i++) {
        obj->child[i] = NULL;
    }   
    obj->end = 0;

    return obj;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char * word) {
    Trie* p = obj;

    int i = 0;
    int len = strlen(word);
    while(i < len){
        int index = word[i]-'a';
        if(p->child[index] == NULL)
        {
            Trie *t = malloc(sizeof(*t));
            t->data = word[i];
            t->end = 0;
            for (int i = 0; i < CHILD_SIZE; i++) {
                t->child[i] = NULL;
            } 
            p->child[index] = t;
        }
        p = p->child[index];
        i++;
    }
    p->end = 1;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char * word) {
    Trie* p = obj;

    int i = 0;
    int len = strlen(word);
    while(i < len){
        int index = word[i]-'a';
        if(p->child[index] == NULL) {
            return false;
        } else {
            i++;
            p = p->child[index];
        }
    }

    if(p->end) {
        return true;
    } else {
        return false;
    }
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char * prefix) {
    Trie* p = obj;

    int i = 0;
    int len = strlen(prefix);
    while(i < len){
        int index = prefix[i]-'a';
        if(p->child[index] == NULL) {
            return false;
        } else {
            i++;
            p = p->child[index];
        }
    }

    return true;
}

void trieFree(Trie* obj) {
    if (obj == NULL) {
        return;
    }

    for (int i = 0; i < CHILD_SIZE; i++) {
        trieFree(obj->child[i]);

        if (obj->child[i] != NULL) {
            free(obj->child[i]);
        }
    }
}
```

## 双向BFS：

适用于目标节点已知的情况;初始结点向目标结点和目标结点向初始结点同时扩展，直至在两个扩展方向上出现同一个结点，搜索结束；

### 代码模板：

```c
void TBFS()
{
    if(s1.state==s2.state)//起点终点相同时要特判
    {
       //do something
        found=true;
        eturn;
    }
       
    bool found=false;
    memset(visited,0,sizeof(visited));  // 判重数组
    while(!Q1.empty())  Q1.pop();   // 正向队列
    while(!Q2.empty())  Q2.pop();  // 反向队列
    //======正向扩展的状态标记为1，反向扩展标记为2
    visited[s1.state]=1;   // 初始状态标记为1
    visited[s2.state]=2;   // 结束状态标记为2
    Q1.push(s1);  // 初始状态入正向队列
    Q2.push(s2);  // 结束状态入反向队列
    while(!Q1.empty() || !Q2.empty())
    {
        if(!Q1.empty())
            BFS_expand(Q1,true);  // 在正向队列中搜索
        if(found)  // 搜索结束 
            return ;
        if(!Q2.empty())
            BFS_expand(Q2,false);  // 在反向队列中搜索
        if(found) // 搜索结束
            return ;
    }
}

void BFS_expand(queue<Status> &Q,bool flag)
{  
    s=Q.front();  // 从队列中得到头结点s
    Q.pop()
    for( 每个s 的子节点 t )
    {
        t.state=Gethash(t.temp)  // 获取子节点的状态
        if(flag)   // 在正向队列中判断
        {
            if (visited[t.state]!=1）// 没在正向队列出现过
            ｛
                if(visited[t.state]==2)  // 该状态在反向队列中出现过
                {
                    各种操作；
                    found=true；
                    return;
                }
                visited[t.state]=1;   // 标记为在在正向队列中
                Q.push(t);  // 入队
            ｝
        ｝
        else    // 在正向队列中判断
        {
            if (visited[t.state]!=2） // 没在反向队列出现过
            ｛
                if(visited[t.state]==1)  // 该状态在正向向队列中出现过
                {
                    各种操作；
                    found=true；
                    return;
                }
                visited[t.state]=2;  // 标记为在反向队列中
                Q.push(t);  // 入队
            ｝
        ｝
    }            
}       
```
