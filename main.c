#include <stdio.h>
#include <locale.h>

#include "game.h"

#include "libs/gets.h"
#include "libs/compares.h"

void print_error(int error_code);

int main()
{
    setlocale(LC_ALL, "Rus");
    long long int width, height, capacity;
    if (GetLLInt(&width, "Введите ширину игрового поля: ", llint_positive) == EOF)
    {
        return EOF;
    }
    if (GetLLInt(&height, "Введите высоту игрового поля: ", llint_positive) == EOF)
    {
        return EOF;
    }
    if (GetLLInt(&capacity, "Введите вместимость истории: ", llint_positive) == EOF)
    {
        return EOF;
    }
    int result = start_game((size_t) width, (size_t) height, (size_t) capacity);
    if (result != SUCCESS && result != EOF){
        print_error(result);
    } else if (result == EOF)
    {
        return EOF;
    }
    return 0;
}

void print_error(int error_code)
{
    printf("[ERROR] Ошибка завершения программы!\n");
}