/**
 * CS 2110 - Spring 2014 - Homework #12
 * Completed by: Kelsey Maclin
 *
 * list.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    node *ptrN;
    ptrN = malloc(sizeof(*ptrN));
    if (ptrN == NULL)
    {
        printf("creat_node failed.");
        return NULL;
    }
    ptrN->data = data;
    ptrN->next = NULL;
    ptrN->prev = NULL;
    return ptrN;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
    list* l;
    l = malloc(sizeof(*l));
    if (l == NULL)
    {
        printf("create_list failed.");
        return NULL;
    }
    l->size = 0;
    l->head = NULL;
    l->tail = NULL;
    return l;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
    node *ptr = create_node(data);
    if (ptr == NULL)
    {
        printf("push_front failed at node creation.");
    }
    else
    {
        if (llist->head == NULL)
        {
            llist->head = ptr;
            llist->tail = ptr;
            llist->size = llist->size + 1;
        }
        else if (!(llist->head == NULL))
        {
            ptr->next = llist->head;
            (llist->head)->prev = ptr;
            llist->head = ptr;
            llist->size = llist->size + 1;
        }
    }
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
    node *ptr = create_node(data);
    if (ptr == NULL)
    {
        printf("push_back failed at node creation.");
    }
    else
    {
        if (llist->head == NULL)
        {
            llist->head = ptr;
            llist->tail = ptr;
            llist->size = llist->size + 1;
        }
        else if (!(llist->head == NULL))
        {
            ptr->prev = llist->tail;
            (llist->tail)->next = ptr;
            llist->tail = ptr;
            llist->size = llist->size + 1;
        }
    }
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
    if (llist->size == 0)
    {
        printf("list has no data.");
        return NULL;
    }
    void *data = (llist->head)->data;
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember the user should never deal with the linked list nodes.
    return data;
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
    if (llist->size == 0)
    {
        printf("list has no data.");
        return NULL;
    }
    void *data = (llist->tail)->data;
    /// @todo Implement changing the return value!
    return data;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
    if (llist->size == 0)
    {
        printf("list is empty. remove_front failed.");
        return -1;
    }
    if (llist->head == llist->tail)
    {
        llist->size = llist->size - 1;
        node* temp = llist->head;
        llist->head = NULL;
        llist->tail = NULL;
        free_func(temp->data);
        free(temp);
    }
    else
    {
        llist->size = llist->size - 1;
        node* ptr = (llist->head)->next;
        ptr->prev = NULL;
        free_func((llist->head)->data);
        free((llist->head));
        llist->head = ptr;
    }
    return 0;
    /// @todo Implement
    /// @note remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
    if (llist->size == 0)
    {
        printf("list is empty. remove_front failed.");
        return -1;
    }
    if (llist->head == llist->tail)
    {
        llist->size = llist->size - 1;
        node *temp = llist->head;
        llist->head = NULL;
        llist->tail = NULL;
        free_func(temp->data);
        free(temp);
    }
    else
    {
        llist->size = llist->size - 1;
        node* ptr = (llist->tail)->prev;
        ptr->next = NULL;
        free_func((llist->tail)->data);
        free(llist->tail);
        llist->tail = ptr;
    }
    /// @todo Implement
    /// @note Remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.
    return 0;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *        data that's being used in this linked list, allocating space for
  *        every part of that data on the heap. This is some function you must
  *        write yourself for testing, tailored specifically to whatever context
  *        you're using the linked list for in your test.
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
    if (llist->size == 0)
    {
        printf("\nthe list that was to be copied was empty. copy_list failed.");
        return NULL;
    }
    unsigned int count = llist->size;
    list* newlist = create_list();
    if (newlist == NULL)
    {
        printf("copy_list failed at create_list.");
        return NULL;
    }
    node *current = llist->head;
    while (count > 0)
    {
        node* newNode = create_node(copy_func(current->data));
        if (newNode == NULL)
        {
            return NULL;
        }
        if (count == llist->size)
        {
            newlist->head = newNode;
            newlist->tail = newlist->head;
            newlist->size = newlist->size + 1;
        }
        else
        {
            (newlist->tail)->next = newNode;
            newNode->prev = newlist->tail;
            newlist->tail = newNode;
            newlist->size = newlist->size + 1;
        }
        current = current->next;
        count--;
    }
	/// @todo implement
	return newlist;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    ///@note simply return the size of the linked list.  Its that easy!
    return llist->size;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
    if (llist->size == 0)
    {
        return 0;
    }
    node* current = llist->head;
    node* nextptr;
    node* prevptr;
    unsigned int count = llist->size;
    for (int i = 0; i < count; i++)
    {
        nextptr = current->next;
        prevptr = current->prev;
        if (pred_func(current->data))
        {
            if (nextptr != NULL)
            {
                nextptr->prev = prevptr;
            }
            if (prevptr != NULL)
            {
                prevptr->next = nextptr;
            }
            
            if (current == llist->head)
            {
                llist->head = nextptr;
            }
            if (current == llist->tail)
            {
                llist->tail = prevptr;
            }
            free_func(current->data);
            free(current);
            llist->size = llist->size - 1;
        }
        current = nextptr;
      /// @todo Implement
    }
    /// @todo Implement changing the return value!
    /// @note remember to also free all nodes you remove.
    /// @note be sure to call pred_func on the NODES DATA to check if the node needs to be removed.
    /// @note free_func is a function that is responsible for freeing the node's data only.
    return (count - llist->size);
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    if ((llist->size == 0) && (llist->head == NULL))
    {
        return 1;
    }
    ///@note an empty list by the way we want you to implement it has a size of zero and head points to NULL.
    return 0;
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  */
void empty_list(list* llist, list_op free_func)
{
    if (llist->size == 0)
    {
        printf("list is already empty.\n");
    }
    else
    {
        node* current = llist->head;
        node* nextptr;
        while (llist->size != 0)
        {
            nextptr = current->next;
            free_func(current->data);
            free(current);
            if (current == llist->head)
            {
                llist->head = NULL;
            }
            if (current == llist->tail)
            {
                llist->tail = NULL;
            }
            if (nextptr != NULL)
            {
                current = nextptr;
            }
            llist->size = llist->size - 1;
        }
    }
    /// @todo Implement
    /// @note Free all of the nodes not the linked list itself.
    /// @note do not free llist.
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
  if (llist->size == 0)
  {
      printf("the list is empty-cannot traverse an empty list.");
  }
  else
  {
      node* current = llist->head;
      for (int i = 0; i < (llist->size); i++)
      {
          do_func(current->data);
          if (current->next != NULL)
          {
              current = current->next;
          }
        /// @todo Implement
      }
  }
}