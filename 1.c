#include <stdio.h>
#include <stdlib.h>
#include "linked_lists.h"
#include <time.h>
#include <unistd.h> 

int main(void)
{
    srand(time(NULL) ^ (getpid() << 16));
    int r = rand();
    node* list = NULL;

    prepend_list(&list, -1);
    append_list(&list, -1);
    print_elements(&list, 3);
    print_elements_reversed(&list, 3);
    insert_element(&list, 1, 22);

    for ( int i = 0; i < 1000; i++ )
        insert_up_sorted(&list, ((rand()) % 300));

        print_list(&list);
        print_list_reversed(&list);
        
        printf("\n[%d]\n", list_size(&list));
        free_list(&list);

    return 0; 
}

