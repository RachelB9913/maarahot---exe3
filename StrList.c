#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

/* StrList represents a StrList data structure. */
typedef struct _node {  //each node is a string which is an array of chars
    char * _data;
    struct _node * _next;
} Node; 

struct _StrList {
    struct _node * _head;
    size_t _size;
}; 
typedef struct _StrList StrList;

#define CREATE_CURRENT Node * current = StrList->_head; 

/* Allocates a new empty StrList. It's the user responsibility to free it with StrList_free. */
StrList* StrList_alloc(){
    StrList* list = (StrList*)malloc(sizeof(StrList));  
    //if (list != NULL) {
    list->_head = NULL;
    list->_size = 0;
    //}
    return list;
}

/* Frees the memory and resources allocated to StrList. If StrList==NULL does nothing (same as free). */
void StrList_free(StrList* StrList) {
    if (StrList == NULL) {
        //printf("\n");
        return; // Check if StrList is NULL
    }
    
    CREATE_CURRENT // Initialize current to the head of the list
    
    while (current) {
        Node* next = current;
        current= current->_next;
        free(next); // Free the node
    }
    free(StrList); // Free the list structure itself
}

/* Returns the number of elements in the StrList. */
size_t StrList_size(const StrList* StrList){
    return StrList->_size;
}

/* Inserts an element in the end of the StrList. */
//first we need to be able to create a new empty node:
Node * createNode(const char * data) {
    Node * newNode = (Node *)malloc(sizeof(Node)+1);
    if(newNode!=NULL){ //if malloc returns null - something failed
        //newNode->_data = data;
        newNode->_data = strdup(data);
        newNode->_next = NULL;
        return newNode;
    }
    return NULL;
}

//and now to add it to the list
void StrList_insertLast(StrList* StrList, const char* data){
    Node * newNode = createNode(data);
    //if the list is empty add the node to be the head of the list
    if(StrList->_head==NULL){
        StrList->_head = newNode;
    }
    //if the list isn't empty - add to the last: the current last will point to the newNode.
    else{
        CREATE_CURRENT
        while(current->_next != NULL){
            current = current->_next;  //in the end of the loop current will be the last node in the list
        }
        current->_next = newNode;
    }
    StrList->_size++; //update the size of the list
}

/* Inserts an element at given index */
//this function will also use the create node function
void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if (index < 0 || index > StrList->_size) // Check for invalid index
        return;
    Node* newNode = createNode(data);
    int i;
    if (index == 0) {
        newNode->_next = StrList->_head;
        StrList->_head = newNode;
        StrList->_size++; // Update the size of the list
    }
    else if (index == StrList->_size) {
        StrList_insertLast(StrList, data);
    }
    else {
        Node* current = StrList->_head;
        for (i = 0; i < index - 1; i++) {
            current = current->_next;
        }
        newNode->_next = current->_next;
        current->_next = newNode;
        StrList->_size++; // Update the size of the list
    }
}

/* Returns the StrList first data. */
char* StrList_firstData(const StrList* StrList){
    if (StrList->_head != NULL) {
        return StrList->_head->_data;
    }
    return NULL;
}

/* Prints the StrList to the standard output. */
void StrList_print(const StrList* StrList){
    if(StrList->_head != NULL){
        CREATE_CURRENT
        printf("%s",current->_data);
        current = current->_next;
        while(current != NULL){
            printf(" %s", current->_data);
            current = current->_next;
            //printf("\n");
        }
    }
    return;
}

/* Prints the word at the given index to the standard output. */
void StrList_printAt(const StrList* Strlist,int index){
    int i;
    if(Strlist != NULL){
        Node * current = Strlist->_head;
        for(i=0;i<index;i++){
            current = current->_next;
        }
        if(current != NULL){
            printf("%s", current->_data);
        }
        else{
            printf("the string is empty\n");  //צריך???????????
        }
    }
    return;
}

/* Return the amount of chars in the list. */
int StrList_printLen(const StrList* Strlist){
    int count = 0;
    Node * current = Strlist->_head;
    while(current != NULL){
        count = count + strlen(current->_data);
        current = current->_next;
    }
    return count;
}

/* Given a string, return the number of times it exists in the list. */
int StrList_count(StrList* StrList, const char* data){
    CREATE_CURRENT
    int isEqual, count=0;
    while(current != NULL){
        isEqual = strcmp(data,current->_data);
        if(isEqual==0){
            count++;
        }
        current=current->_next;
    }
    return count;
}

/* Given a string and a list, remove all the appearences of this string in the list. */
void StrList_remove(StrList* StrList, const char* data) {
    CREATE_CURRENT
    Node* prev = NULL;
    int isEqual;

    while (current != NULL) {
        isEqual = strcmp(data, current->_data);
        
        if (isEqual == 0) {  // If it is a string we need to remove
            if (prev == NULL) {  // If it is the first string and we want to remove it
                StrList->_head = current->_next;
            } else {  // To remove - the previous node will now point to the next node removing the current one
                prev->_next = current->_next;
            }
            // We need to free the memory taken by the current node we just removed
            free(current->_data);
            free(current);
            if (prev != NULL) {
                current = prev->_next;  // Update current if it's not the head
            } else {
                current = StrList->_head;  // Update current if it's the head
            }
            StrList->_size--;
        } else {  // If we don't need to remove the string - change the prev to be the current and the current to be the next node
            prev = current;
            current = current->_next;
        }
    }
}

/* Given an index and a list, remove the string at that index. */
void StrList_removeAt(StrList* StrList, int index){
    if(StrList == NULL) {
        return;
    }
    // Check for invalid index or empty list
    if(index < 0 || index >= StrList->_size || StrList->_head == NULL) 
        return;

    CREATE_CURRENT
    Node *prev = NULL; // Initialize prev pointer
    int i;

    if(index == 0){
        StrList->_head = current->_next;
    }
    else{
        for(i = 0; i < index; i++){
            prev = current;
            current = current->_next;
        }
        if(prev != NULL)
            prev->_next = current->_next;
    }
    // Free memory for the data and node at the specified index
    free(current->_data);
    free(current);
    StrList->_size--;
}


/* Checks if two StrLists have the same elements - 
/ returns 0 if not and any other number if yes */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    int isEqual;
    if(StrList1==NULL && StrList2==NULL){
        return 1;
    }
    if((StrList1==NULL && StrList2!=NULL)||(StrList1!=NULL && StrList2==NULL)){
        return 0;
    }

    Node * curr1 = StrList1->_head;
    Node * curr2 = StrList2->_head;
    
    if(StrList1->_size != StrList2->_size){
        return 0;
    }
    else{
        while(curr1!=NULL){
            isEqual = strcmp(curr1->_data,curr2->_data);
            if(isEqual!=0){  //if the strings aren't the same return the number the function gave you (!=0 if the strings are different)
                return 0;
            }
            else{  //if these string were the same check the next 2 in the lists
                curr1=curr1->_next;
                curr2=curr2->_next;
            }
        }
        //if the while loop finished and it didn't return 0 already = the lists have the same elements
        return 1;
    }
}

/* Clones the given StrList. - It's the user responsibility to free it with StrList_free. */
StrList* StrList_clone(const StrList* StrList){
    struct _StrList* the_new = StrList_alloc();
    Node * old_curr = StrList->_head;
    while(old_curr!=NULL){
        StrList_insertLast(the_new, old_curr->_data); // Inserting data from original list to clone list
        old_curr=old_curr->_next;
    }
    return the_new;
}

/* Reverces the given StrList. */
void StrList_reverse(StrList* StrList) {
    if(StrList==NULL){
        return;
    }
    Node *prev = NULL;
    Node *current = StrList->_head;
    Node *next = NULL;

    // Traverse the list and reverse the links between nodes
    while (current != NULL) {
        next = current->_next;  // Store the next node
        current->_next = prev;  // Reverse the pointer

        // Move pointers one position ahead
        prev = current;
        current = next;
    }
    // Update the head to point to the new first node (which was previously the last node)
    StrList->_head = prev;
}

/* Sort the given list in lexicographical order  */
void StrList_sort(StrList* StrList){
    Node *i, *j;
    char* temp;
    if(StrList==NULL){
        return;
    }
    if (StrList->_head == NULL || StrList->_head->_next == NULL)
        return;
    for (i = StrList->_head; i->_next != NULL; i = i->_next) {    
        for (j = StrList->_head; j->_next != NULL; j = j->_next) {
            if (strcmp(j->_data, j->_next->_data) > 0) {
                temp = j->_data;
                j->_data = j->_next->_data;
                j->_next->_data = temp;
            }
        }
    }
}

/* Checks if the given list is sorted in lexicographical order 
 * returns 1 for sorted,   0 otherwise */
int StrList_isSorted(StrList* StrList){
    int isSorted;
    struct _StrList* checkList = StrList_alloc(); 
    checkList = StrList_clone(StrList);  //clones the given StrList to a new StrList 
    StrList_sort(checkList);             //sorts the new list using the sort function 
    //checks if the given list was sorted from the beginning. if it was sorted the StrList_sort(checkList) line will not change the list
    isSorted = StrList_isEqual(StrList,checkList); 
    StrList_free(checkList);
    
    return isSorted;  //returns 0 if the lists are different which means the given list wasn't sorted and 1 otherwise
}


