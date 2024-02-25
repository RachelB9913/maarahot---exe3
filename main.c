#include "StrList.h"
#include <stdio.h>
#include <string.h>

int main(){
    int num_words, i, word_len, chosen_num=1;
    char* word = (char*)malloc(25*sizeof(char));
    StrList* list = StrList_alloc();

    while(chosen_num>0 && chosen_num<14){
        scanf(" %d" , &chosen_num);
        if(chosen_num == 1){
            scanf(" %d" , &num_words);
            for(i=0;i<num_words;i++){
                scanf(" %s" , word);
                word_len = strlen(word);
                char* temp = (char*)realloc(word, word_len*sizeof(char)+1); //change the dinamyc size of the String to be the exact size of it + /0
                StrList_insertLast(list, temp);
            }
        }
        else if(chosen_num == 2){
            int index=0;
            char* word = (char*)malloc(25*sizeof(char));
            scanf(" %d", &index);
            scanf(" %s", word);
            word_len = strlen(word);
            char* temp = (char*)realloc(word, word_len*sizeof(char)+1); //change the dinamyc size of the String to be the exact size of it + /0
            StrList_insertAt(list, temp, index);
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
            scanf(" %s", word);
            count = StrList_count(list, word);
            printf("%d", count);
            printf("\n");
        }
        else if(chosen_num == 8){
            char* word = (char*)malloc(25*sizeof(char));
            scanf(" %s", word);
            StrList_remove(list, word);
        }
        else if(chosen_num == 9){
            int index=0;
            scanf(" %d", &index);
            StrList_removeAt(list, index);
        }
        else if(chosen_num == 10){
            StrList_reverse(list);
        }
        else if(chosen_num == 11){
            StrList_free(list);
            list = StrList_alloc();
        }
        else if(chosen_num == 12){
            StrList_sort(list);
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

