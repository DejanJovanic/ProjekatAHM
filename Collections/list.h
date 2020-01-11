#pragma once
#include "stdlib.h"
#include <wtypes.h>
typedef struct list_node {
	void* data;
	struct list_node* next;
} Node;

BOOL list_add_node(Node** heap_list_head, HANDLE heap_handle);
void list_delete_list(Node** head_ref);