#include <stdio.h>
#include <stdlib.h>
#include "mergeTwoLists.h"

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    if (l1 == NULL && l2 == NULL) {
        return NULL;
    }

    if (l1 == NULL) {
        return l2;
    }

    if (l2 == NULL) {
        return l1;
    }

    struct ListNode* head = NULL;
    struct ListNode* h = NULL;
    
    while (l1 != NULL || l2 != NULL) {
        struct ListNode* tmp = NULL;
        if (l1 && l2){
            if (l1->val <= l2->val) {
                tmp = l1;
                l1 = l1->next;
            } else {
                tmp = l2;
                l2 = l2->next;
            }
        } else if (l1) {
            tmp = l1;
            l1 = l1->next;
        } else {
            tmp = l2;
            l2 = l2->next;
        }

        if (h) {
            h->next = tmp;
            h = h->next;
        } else {
            head = tmp;
            h = head;
        }
    }

    return head;
}

