#include "lab.h"

/**
* @brief Create a new list with callbacks that know how to deal with the data
that
* list is storing. The caller must pass the list to list_destroy when finished
to
* free any memory that was allocated.
*
* @param destroy_data Function that will free the memory for user supplied data
* @param compare_to Function that will compare two user data elements
* @return struct list* pointer to the newly allocated list.
*/
list_t *list_init(void (*destroy_data)(void *),
int (*compare_to)(const void *, const void *)){
    list_t* out = (list_t*) malloc(sizeof(list_t));
    out->size = 0;
    out->compare_to = *compare_to;
    out->destroy_data = *destroy_data;

    node_t* head = (node_t*) malloc(sizeof(node_t));
    head->data = NULL;
    head->next = head;
    head->prev = head;
    out->head = head;
}
/**
* @brief Destroy the list and and all associated data. This functions will
call
* destroy_data on each nodes data element.
*
* @param list a pointer to the list that needs to be destroyed
*/
void list_destroy(list_t **list){
    if (list == NULL){
        return;
    }
    list_t* target = *list;
    node_t* target_node = target->head->next;
    node_t* next_target_node;

    /**
     * loop starts at first element of the list
     * then increments size of list, so sentinel node will be freed
     */
    for (int i = 0; i < target->size ; i++)
    {
        if (target_node->data != NULL){
            target->destroy_data(target_node->data);
        }

        if (target_node->next != NULL){
            next_target_node = target_node->next;
        }

        free(target_node);
        target_node = next_target_node;
    }

    free(target);
    
}
/**
* Adds data to the front of the list
*
* @param list a pointer to an existing list.
* @param data the data to add
* @return A pointer to the list
*/
list_t *list_add(list_t *list, void *data){
    if (list == NULL){
        return NULL;
    }
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    node_t* sec_node = list->head->next;
    new_node->data = data;
    new_node->next = sec_node;
    new_node->prev = list->head;
    list->head->next = new_node;
    sec_node->prev = new_node;

}
/**
* @brief Removes the data at the specified index. If index is invalid
* then this function does nothing and returns NULL
*
* @param list The list to remove the element from
* @param index The index
* @return void* The data that was removed or NULL if nothing was removed
*/
void *list_remove_index(list_t *list, size_t index){
    if (list == NULL){
        return NULL;
    }
    
    node_t* curr_node = list->head;
    void* out = NULL;
    if (index<list->size){
        
        for (size_t i = 0; i <= index; i++){
            curr_node = curr_node->next;
        }
        out = curr_node->data;
        curr_node->prev->next = curr_node->next;
        curr_node->next->prev = curr_node->prev;
        free(curr_node);
        
    }
    return out;
}
/**
* @brief Search for any occurrence of data from the list.
* Internally this function will call compare_to on each item in the list
* until a match is found or the end of the list is reached. If there are
* multiple copies of the same data in the list the first one will be returned.
*
* @param list the list to search for data
* @param data the data to look for
* @return The index of the item if found or -1 if not
*/
int list_indexof(list_t *list, void *data){
    if (list == NULL){
        return -1;
    }
    node_t* curr_node = list->head->next;
    for (size_t i = 0; i < list->size-1; i++){
        if (list->compare_to(curr_node->data,data)==0){
            return i;
        }
        curr_node = curr_node->next;
        
    }
    return -1;
}
