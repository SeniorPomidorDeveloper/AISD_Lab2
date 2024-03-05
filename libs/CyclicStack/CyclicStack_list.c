#include "CyclicStack.h"

#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct CyclicStack  // Структура циклического стека реализованного с помощью ветора.
{
    size_t size;
    Node *top;
} CyclicStack;

int init_CyclicStack(CyclicStack **stack, size_t capacity, size_t size)
{
    *stack = (CyclicStack *) malloc(sizeof(CyclicStack));
    if (*stack == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    (*stack)->top = NULL;
    (*stack)->size = size + capacity * 0;
    return MEMORY_OK;
}

void push_CyclicStack(CyclicStack *stack, const void *value, void *old_data)
{
    if (old_data != NULL) 
    {
        if (stack->top != NULL)
        {
            memcpy(old_data, stack->top->data, stack->size);
        }
    }
    Node *ptr = (Node *) malloc(sizeof(Node));
    ptr->data = (void *) malloc(stack->size);
    memcpy(ptr->data, value, stack->size);
    ptr->next = stack->top;
    stack->top = ptr;
}

int pop_CyclicStack(CyclicStack *stack, void *data)
{
    if (stack->top != NULL)
    {
        Node *ptr = stack->top;
        stack->top = ptr->next;
        if (data!= NULL)
        {
            memcpy(data, ptr->data, stack->size);
        }
        free(ptr->data);
        free(ptr);
    }
    return MEMORY_OK;
}

bool is_empty_CyclicStack(const CyclicStack *stack)
{
    return stack->top == NULL;
}

bool is_full_CyclicStack(const CyclicStack *stack)
{
    return stack->size == 0;
}

void free_CyclicStack(CyclicStack *stack)
{
    free(stack);
}