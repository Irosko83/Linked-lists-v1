#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *previous;
} node;

void prepend_list(node **list, int new_data);
void append_list(node **list, int new_data);
void insert_element(node **list, int location, int value);
void print_elements(node **list, int number_of_elements);
void print_elements_reversed(node **list, int number_of_elements);
void print_list(node **list);
void print_list_reversed(node **list);
int index_for_down_sorted_insert(node **list, int value);
int index_for_up_sorted_insert(node **list, int value);
void insert_down_sorted(node **list, int value);
void insert_up_sorted(node **list, int value);
int list_size(node **list);
void free_list(node **list);
