#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "myCircularDeque.h"

/** Initialize your data structure here. Set the size of the deque to be k. */

MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    obj->head = NULL;
    obj->tail = NULL;
    obj->curSize = 0;
    obj->maxSize = k;

    return obj;
}

/** Adds an item at the front of Deque. Return true if the operation is successful. */
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if (obj == NULL || obj->curSize == obj->maxSize) {
        return false;
    }

    struct myDLNode *temp = (struct myDLNode*)malloc(sizeof(struct myDLNode));
    temp->val = value;
    if (obj->head) {
        temp->next = obj->head;
        temp->prev = NULL;
        obj->head->prev = temp;
        obj->head = temp;
    } else {
        obj->head = temp;
        obj->tail = temp;
        obj->head->next = obj->tail;
        obj->tail->prev = obj->head;
    }

    obj->curSize++;
    return true;
}

/** Adds an item at the rear of Deque. Return true if the operation is successful. */
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if (obj == NULL || obj->curSize == obj->maxSize) {
        return false;
    }

    struct myDLNode *temp = (struct myDLNode*)malloc(sizeof(struct myDLNode));
    temp->val = value;
    if (obj->tail) {
        temp->prev = obj->tail;
        temp->next = obj->head;
        obj->tail->next = temp;
        obj->tail = temp;
    } else {
        obj->head = temp;
        obj->tail = temp;
        obj->head->next = obj->tail;
        obj->tail->prev = obj->head;
    }

    obj->curSize++;
    return true;  
}

/** Deletes an item from the front of Deque. Return true if the operation is successful. */
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if (obj == NULL || obj->curSize == 0) { 
        return false;
    }

    struct myDLNode *temp = obj->head;
    if (obj->curSize > 1) {
        temp->next->prev = obj->tail;
        obj->tail->next = temp->next;
        obj->head = temp->next;
    } else {
        obj->tail = NULL;
        obj->head = NULL;
    }

    free(temp);
    obj->curSize--;
    return true;    
}

/** Deletes an item from the rear of Deque. Return true if the operation is successful. */
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if (obj == NULL || obj->curSize == 0) { 
        return false;
    }

    struct myDLNode *temp = obj->tail;
    if (obj->curSize > 1) {
        temp->prev->next = obj->head;
        obj->head->prev = temp->prev;
        obj->tail = temp->prev;
    } else {
        obj->tail = NULL;
        obj->head = NULL;
    }

    free(temp);
    obj->curSize--;
    return true;      
}

/** Get the front item from the deque. */
int myCircularDequeGetFront(MyCircularDeque* obj) {
    if (obj && obj->head) { 
        return obj->head->val;
    }

    return -1;
}

/** Get the last item from the deque. */
int myCircularDequeGetRear(MyCircularDeque* obj) {
    if (obj && obj->tail) { 
        return obj->tail->val;
    }

    return -1;  
}

/** Checks whether the circular deque is empty or not. */
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    if (obj && obj->curSize == 0) { 
        return true;
    }

    return false;    
}

/** Checks whether the circular deque is full or not. */
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    if (obj && obj->curSize == obj->maxSize) { 
        return true;
    }

    return false;      
}

void myCircularDequeFree(MyCircularDeque* obj) {
    if (obj && obj->curSize) {
        while(obj->curSize && obj->head) {
            struct myDLNode *temp = obj->head;
            obj->head = temp->next;
            free(temp);
            obj->curSize--;  
        }

        free(obj);
    }
}

/**
 * Your MyCircularDeque struct will be instantiated and called as such:
 * MyCircularDeque* obj = myCircularDequeCreate(k);
 * bool param_1 = myCircularDequeInsertFront(obj, value);
 
 * bool param_2 = myCircularDequeInsertLast(obj, value);
 
 * bool param_3 = myCircularDequeDeleteFront(obj);
 
 * bool param_4 = myCircularDequeDeleteLast(obj);
 
 * int param_5 = myCircularDequeGetFront(obj);
 
 * int param_6 = myCircularDequeGetRear(obj);
 
 * bool param_7 = myCircularDequeIsEmpty(obj);
 
 * bool param_8 = myCircularDequeIsFull(obj);
 
 * myCircularDequeFree(obj);
*/
