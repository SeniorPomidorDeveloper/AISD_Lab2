#ifndef CYCLICSTACK_H
#define CYCLICSTACK_H

#include <stddef.h>
#include <stdbool.h>

enum memory_errors
{
    MEMORY_OK,
    MEMORY_ALLOCATION_ERROR
};

typedef struct CyclicStack CyclicStack;  // Структура циклического стека реализованного с помощью ветора.

int init_CyclicStack(CyclicStack **stack, size_t len, size_t size);    // Инициализация стека.
void push_CyclicStack(CyclicStack *stack, const void *value, void *old_data);   // Добавление элемента в стек.
int pop_CyclicStack(CyclicStack *stack, void *data);    // Получение элемента из стека.
bool is_empty_CyclicStack(const CyclicStack *stack);    // Проверка наличия элементов в стеке
bool is_full_CyclicStack(const CyclicStack *stack);    // Проверка наличия места для нового элемента в стек
void free_CyclicStack(CyclicStack *stack);    // Освобождение памяти отведённой под стек.

#endif //CyclicStack_H