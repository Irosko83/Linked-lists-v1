#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Define a node structure for a doubly-linked list
typedef struct node {
    int data;
    struct node *next;      // Pointer to the next node in the list
    struct node *previous;  // Pointer to the previous node in the list
} node;

// Function to prepend a new node with given data to the beginning of the list
void prepend_list(node **list, int new_data) {
    // Allocate memory for a new node
    node *new_node = malloc(sizeof(node));
    new_node->data = new_data;
    new_node->next = *list;
    new_node->previous = NULL;
    
    // Update the previous pointer of the current head if the list is not empty
    if (*list != NULL)
        (*list)->previous = new_node;
    
    // Update the head of the list to the new node
    *list = new_node;
}

// Function to append a new node with given data to the end of the list
void append_list(node **list, int new_data) {
    // Traverse to the end of the list
    node *temporary = *list;
    while (1) {
        if (temporary->next != NULL)
            temporary = temporary->next;
        else
            break;
    }

    // Allocate memory for a new node
    node *new_node = malloc(sizeof(node));
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->previous = temporary;

    // Update the next pointer of the last node in the list
    temporary->next = new_node;
}

// Function to insert a new node with given data at a specified location in the list
void insert_element(node **list, int location, int value) {
    node *new_node = malloc(sizeof(node));
    node *temporary_right = *list;
    node *temporary_left;

    // Check for invalid index (negative)
    if (location < 0) {
        perror("Insertion failed, index can't be negative");
        free(new_node);
        exit(1);
    }

    // Handle insertion at the beginning (prepend)
    if (location == 0) {
        prepend_list(list, value);
        free(new_node);
        return;
    }

    // Traverse to the specified location in the list
    for (int i = 0; i < location; i++) {
        temporary_right = temporary_right->next;
        // Check for an invalid index (too large)
        if (temporary_right == NULL && i + 1 != location) {
            perror("Error, index too large");
            free(new_node);
            return;
        }
        // Handle insertion at the end (append)
        else if (temporary_right == NULL && i + 1 == location) {
            append_list(list, value);
            free(new_node);
            return;
        }
    }

    // Connect the new node to the surrounding nodes
    new_node->next = temporary_right;
    new_node->previous = temporary_right->previous;

    temporary_left = temporary_right->previous;
    temporary_right->previous = new_node;

    temporary_left->next = new_node;
    new_node->data = value;
}

// Function to print the specified number of elements in the list
void print_elements(node **list, int number_of_elements) {
    node *temporary = *list;
    for (int i = 0; i < number_of_elements; i++) {
        if (temporary == NULL)
            perror("List shorter than the number You asked for.");
        printf("%d \n", temporary->data);
        temporary = temporary->next;
        if (temporary == NULL)
            break;
    }
}

// Function to print the specified number of elements in the list in reverse order
void print_elements_reversed(node **list, int number_of_elements) {
    node *temporary = *list;
    for (int i = 1; i < number_of_elements; i++) {
        if ((temporary->next) != NULL)
            temporary = temporary->next;
    }
    for (int i = 0; i < number_of_elements; i++) {
        printf("%d \n", temporary->data);
        if ((temporary->previous) != NULL)
            temporary = temporary->previous;
        else
            break;
    }
}

// Function to print all elements in the list
void print_list(node **list) {
    node *temporary = *list;
    int i = 0;
    while (1) {
        if (temporary == NULL)
            printf("List empty.");

        printf("%3d \n", temporary->data);

        temporary = temporary->next;
        if (temporary == NULL)
            break;
        i++;
    }
}

// Function to print all elements in the list in reverse order
void print_list_reversed(node **list) {
    node *temporary = *list;
    int i = 0;
    while (1) {
        if ((temporary->next) != NULL)
            temporary = temporary->next;
        else
            break;
    }

    while (1) {
        printf("%d \n", temporary->data);
        temporary = temporary->previous;
        if (temporary == NULL)
            break;
        i++;
    }
}

// Function to determine the index for inserting an element in a down-sorted list
int index_for_down_sorted_insert(node **list, int value) {
    int index = 0;
    node *temporary = *list;

    // Check for an empty list
    if (temporary == NULL)
        return 0;

    // Traverse the list to find the appropriate index
    while (1) {
        if (temporary == NULL || temporary->data <= value) {
            break;
        } else if (temporary != NULL) {
            temporary = temporary->next;
            index++;
        }
    }
    return index;
}

// Function to determine the index for inserting an element in an up-sorted list
int index_for_up_sorted_insert(node **list, int value) {
    int index = 0;
    node *temporary = *list;

    // Check for an empty list
    if (temporary == NULL)
        return 0;

    // Traverse the list to find the appropriate index
    while (1) {
        if (temporary == NULL || temporary->data >= value) {
            break;
        } else if (temporary != NULL) {
            temporary = temporary->next;
            index++;
        }
    }
    return index;
}

// Function to insert an element into a down-sorted list
void insert_down_sorted(node **list, int value) {
    // Use the previously defined function with the appropriate index
    insert_element(list, index_for_down_sorted_insert(list, value), value);
}

// Function to insert an element into an up-sorted list
void insert_up_sorted(node **list, int value) {
    // Use the previously defined function with the appropriate index
    insert_element(list, index_for_up_sorted_insert(list, value), value);
}

// Function to determine the size of the list
int list_size(node **list) {
    int counter = 0;
    node *temporary = *list;
    while (1) {
        if (temporary == NULL)
            break;
        counter++;
        temporary = temporary->next;
    }
    return counter;
}

// Function to free the memory allocated for the list
void free_list(node **list) {
    if (*list == NULL) {
        return;
    }

    node *current = *list;
    node *next_node;

    // Traverse the list and free each node
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    // Set the list to NULL after freeing all nodes
    *list = NULL;
}
