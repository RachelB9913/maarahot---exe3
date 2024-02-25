#include "StrList.h"
#include <stdio.h>
#include <string.h>

int main(){
    int num_words, i, word_len, chosen_num=1;
    char* word = (char*)malloc(25*sizeof(char));
    StrList* list = StrList_alloc();

    // printf("Menu:\n");
    //     printf("1 - Insert strings into the list\n");
    //     printf("2 - Insert a string at a certain index\n");
    //     printf("3 - Print the list\n");
    //     printf("4 - Print the length of the list\n");
    //     printf("5 - Print a string at a certain index\n");
    //     printf("6 - Print the number of characters in the entire list\n");
    //     printf("7 - Print how many times a string appears\n");
    //     printf("8 - Delete all occurrences of a string from the list\n");
    //     printf("9 - Delete a member at a certain index\n");
    //     printf("10 - Reverse the list\n");
    //     printf("11 - Delete the entire list\n");
    //     printf("12 - Sort the list in lexicographical order\n");
    //     printf("13 - Check whether the list is sorted in lexicographical order\n");
    //     printf("0 - Exit\n");
    //     printf("Enter your option: ");

    
    while(chosen_num>0 && chosen_num<14){
        //printf("\nEnter your option: ");
        scanf(" %d" , &chosen_num);
        if(chosen_num == 1){
            //printf("please enter the number of words you'd like to enter and the words.\n");
            scanf(" %d" , &num_words);
            for(i=0;i<num_words;i++){
                scanf(" %s" , word);
                word_len = strlen(word);
                //char* temp;
                char* temp = (char*)realloc(word, word_len*sizeof(char)+1); //change the dinamyc size of the String to be the exact size of it + /0
                StrList_insertLast(list, temp);
                //printf("inserted %s to the list and the length of the string after realloc is: %ld\n", temp, strlen(temp));
            }
        }
        else if(chosen_num == 2){
            int index=0;
            char* word = (char*)malloc(25*sizeof(char));
            //printf("in what index you want to enter a word?");
            scanf(" %d", &index);
            //printf("which word would you like to add?");
            scanf(" %s", word);
            word_len = strlen(word);
            //char* temp;
            char* temp = (char*)realloc(word, word_len*sizeof(char)+1); //change the dinamyc size of the String to be the exact size of it + /0
            StrList_insertAt(list, temp, index);
            //StrList_print(list);
        }
        else if(chosen_num == 3){
            StrList_print(list);
            printf("\n");
        }
        else if(chosen_num == 4){
            size_t list_size = StrList_size(list);
            printf("%ld", list_size);
            printf("\n");
        }
        else if(chosen_num == 5){
            int index=0;
            //printf("choose an index ");
            scanf(" %d", &index);
            StrList_printAt(list, index);
            printf("\n");
        }
        else if(chosen_num == 6){
            int len = 0;
            len = StrList_printLen(list);
            printf("%d", len);
            printf("\n");
        }
        else if(chosen_num == 7){
            int count=0;
            char* word = (char*)malloc(25*sizeof(char));
            //printf("which word would you like to add?");
            scanf(" %s", word);
            count = StrList_count(list, word);
            printf("%d", count);
            printf("\n");
        }
        else if(chosen_num == 8){
            char* word = (char*)malloc(25*sizeof(char));
            //printf("which word would you like to remove?");
            scanf(" %s", word);
            StrList_remove(list, word);
        }
        else if(chosen_num == 9){
            int index=0;
            //printf("choose an index to remove");
            scanf(" %d", &index);
            StrList_removeAt(list, index);
            //StrList_print(list);
        }
        else if(chosen_num == 10){
            StrList_reverse(list);
            //StrList_print(list);
        }
        else if(chosen_num == 11){
            StrList_free(list);
            list = StrList_alloc();
            //printf("the list is empty now");
        }
        else if(chosen_num == 12){
            StrList_sort(list);
            //StrList_print(list);
        }
        else if(chosen_num == 13){
            int isSorted = 0;
            isSorted= StrList_isSorted(list);
            if(isSorted==1){
                printf("true\n");
            }
            else{
                printf("false\n");
            }
        }
        else if(chosen_num==14){
            StrList* copied = StrList_alloc();
            char* first = StrList_firstData(list);
            printf("the first data is %s",first);
            copied = StrList_clone(list);
            int isEqual = StrList_isEqual(list,copied);
            if(isEqual){
                printf("the lists are the same ");
            }
            else{
                printf("the lists are different");
            }
        }
    } 
    return 0;
}

