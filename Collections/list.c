#include "list.h"


BOOL list_add_node(Node** heap_list_head, HANDLE heap_handle) {
    if (heap_handle != NULL) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node != NULL) {
            new_node->data = heap_handle;
            new_node->next = (*heap_list_head);

            (*heap_list_head) = new_node;
            return TRUE;
        }
    }
    return FALSE;
}

void list_delete_list(Node** head_ref)
{
    Node* current = *head_ref;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}