#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

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

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/
