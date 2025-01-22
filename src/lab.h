#ifndef LAB_H
#define LAB_H
#include <stdlib.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
{
#endif
/**
* @brief A node in the list
*
*/
typedef struct node{
  void *data;
  struct node *next;
  struct node *prev;
} node_t;

#ifdef __cplusplus
}
#endif
#endif
