#include "CyclicStack.h"

#include <stdlib.h>
#include <string.h>

typedef struct CyclicStack  // Структура циклического стека реализованного с помощью ветора.
{
    size_t capacity;
    size_t len;
    size_t size;
    size_t top;
    void *data;
} CyclicStack;

int init_CyclicStack(CyclicStack **stack, size_t capacity, size_t size)
{
    *stack = (CyclicStack *) malloc(sizeof(CyclicStack));
    if (*stack == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    (*stack)->top = 0;
    (*stack)->capacity = capacity;
    (*stack)->len = 0;
    (*stack)->size = size;
    (*stack)->data = (void *) malloc((*stack)->capacity * (*stack)->size);
    if ((*stack)->data == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    return MEMORY_OK;
}

void push_CyclicStack(CyclicStack *stack, const void *value, void *old_data)
{
    if (old_data != NULL) 
    {
       memcpy(old_data, stack->data + stack->top * stack->size, stack->size);
    }
    memcpy(stack->data + stack->top * stack->size, value, stack->size);
    stack->top++;
    stack->top %= stack->capacity;
    if (stack->len != stack->capacity) 
    {
        stack->len++;
    }
}

int pop_CyclicStack(CyclicStack *stack, void *data)
{
    if (stack->top == 0) 
    {
        stack->top = stack->capacity - 1;
    } else
    {
        stack->top--;
    }
    memcpy(data, stack->data + stack->top * stack->size, stack->size);
    stack->len--;
    return MEMORY_OK;
}

bool is_empty_CyclicStack(const CyclicStack *stack)
{
    return stack->len == 0;
}

bool is_full_CyclicStack(const CyclicStack *stack)
{
    return stack->len == stack->capacity;
}

void free_CyclicStack(CyclicStack *stack)
{
    free(stack->data);
    free(stack);
}