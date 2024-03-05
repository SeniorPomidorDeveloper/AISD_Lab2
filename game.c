#include "game.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "libs/gets.h"
#include "libs/compares.h"

int create_new_point(Game *game, Field *field, Point *point)
{
    if (point->x > game->width || point->y > game->height)
    {
        return COORDINATE_ERROR;
    }
    field->points[point->y][point->x] = true;
    return SUCCESS;
}

int input_points(Game *game, Field *field)
{
    long long int count_points;
    if (GetLLInt(&count_points, "Введите кол-во живых точек: ", llint_non_negative) == EOF)
    {
        return EOF;
    }
    for (long long int i = 0; i < count_points; ++i)
    {
        long long int x, y;
        printf("Введите координаты живойх точки: \n");
        if (GetLLInt(&x, "\tx: ", llint_non_negative) == EOF)
        {
            return EOF;
        }
        if (GetLLInt(&y, "\ty: ", llint_non_negative) == EOF)
        {
            return EOF;
        }
        Point point = {(size_t)x, (size_t)y};
        if (create_new_point(game, field, &point) == COORDINATE_ERROR)
        {
            printf("[WARNING] Ошибка ввода координат точки!\n");
            printf("Попробуйте еще раз!\n");
            --i;
        }
    }
    return SUCCESS;
}

void print_menu()
{
    printf("Комманды которые вы можете использовать:\n");
    printf("\t>) Перейти к следующему поколению\n");
    printf("\t<) Перейти к предыдущему поколению\n");
    printf("\tq) Закончить игру\n");
}

int command_menu()
{
    int result;
    do {
        print_menu();
        printf("Введите команду: ");
        char command, symbol = getchar();
        command = symbol;
        while (symbol  != '\n' && symbol != EOF) 
        {
            symbol = getchar();
        }
        if (command == EOF || symbol == EOF)
        {
            return EOF;
        }
        switch (command)
        {
            case '>':
                result = TO_NEXT_GEN;
                break;
            case '<':
                result = TO_PREV_GEN;
                break;
            case 'q':
                result = EXIT;
                break;
            default:
                result = INVALID_COMMAND;
                printf("[WARNING] Такой команды не существует!\n");
                printf("Попробуйте еще раз!\n");
                break;
        }
    } while (result == INVALID_COMMAND);
    return result;
}

unsigned short int count_neighbours(Game *game, Field *field, Point *point) 
{
    Point left_top = {(size_t) (((long int) point->x - 1 < 0) * (game->width - 1)) + (size_t) (((long int) point->x - 1 >= 0) * (point->x - 1)), 
                      (size_t) (((long int) point->y - 1 < 0) * (game->height - 1)) + (size_t) (((long int) point->y - 1 >= 0) * (point->y - 1))};
    Point left = {(size_t) (((long int) point->x - 1 < 0) * (game->width - 1)) + (size_t) (((long int) point->x - 1 >= 0) * (point->x - 1)), 
                  point->y};
    Point left_bottom = {(size_t) (((long int) point->x - 1 < 0) * (game->width - 1)) + (size_t) (((long int) point->x - 1 >= 0) * (point->x - 1)), 
                         (point->y + 1) % game->height};
    Point right_top = {(point->x + 1) % game->width,  
                       (size_t) (((long int) point->y - 1 < 0) * (game->height - 1)) + (size_t) (((long int) point->y - 1 >= 0) * (point->y - 1))};
    Point right = {(point->x + 1) % game->width, 
                   point->y};
    Point right_bottom = {(point->x + 1) % game->width, 
                          (point->y + 1) % game->height};
    Point top = {point->x, (size_t) (((long int) point->y - 1 < 0) * (game->height - 1)) + (size_t) (((long int) point->y - 1 >= 0) * (point->y - 1))};
    Point bottom = {point->x, (point->y + 1) % game->height};
    const size_t len = 8;
    Point *neighbours[] = {&left_top, &left, &left_bottom, &right_top, &right, &right_bottom, &top, &bottom};
    unsigned short int count = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (field->points[neighbours[i]->y][neighbours[i]->x] == true)
        {
            ++count;
        }
    }
    return count;
}
void generate_new_points(Game *game, Field *old_field)
{
    for (size_t i = 0; i < game->height; ++i)
    {
        for (size_t j = 0; j < game->width; ++j)
        {
            Point point = {j, i};
            unsigned short int count = count_neighbours(game, old_field, &point);
            if (count == 3) 
            {
                game->active_field->points[i][j] = true;
            } else if (count < 2 || count > 3) 
            {
                game->active_field->points[i][j] = false;
            } else {
                game->active_field->points[i][j] = old_field->points[i][j];
            }
        }
    }
}

int init_field(Game *game, Field *field)
{
    field->points = (bool **) calloc(game->height, sizeof(bool *));
    if (field->points == NULL)
    {
        return MEMORY_REALLOCATION_ERROR;
    }
    for (size_t i = 0; i < game->height; ++i) 
    {
        field->points[i] = (bool *) calloc(game->width, sizeof(bool));
        if (field->points[i] == NULL)
        {
            return MEMORY_REALLOCATION_ERROR;
        }
    }
    return SUCCESS;
}

void free_field(Game *game, Field *field)
{
    if (field != NULL)
    {
        if (field->points != NULL)
        {
            for (size_t j = 0; j < game->height; ++j)
            {
                if (field->points[j] != NULL)
                {
                    free(field->points[j]);
                }
            }
            free(field->points);
        }
        free(field);
    }
}

int to_next_gen(Game *game) // Доработать
{   
    Field *old_field = NULL;
    if (game->active_field != NULL)
    {
        push_CyclicStack(game->history_field, &(game->active_field), &old_field);
        if (is_full_CyclicStack(game->history_field))
        {
            free_field(game, old_field);
        }
        old_field = game->active_field;
    }
    game->active_field = (Field *) malloc(sizeof(Field));
    if (game->active_field == NULL)
    {
        return MEMORY_REALLOCATION_ERROR;
    }
    if (init_field(game, game->active_field) == MEMORY_REALLOCATION_ERROR)
    {
        return MEMORY_REALLOCATION_ERROR;
    }
    if (old_field != NULL)
    {
        generate_new_points(game, old_field);
    }
    return SUCCESS;
}

void to_prev_gen(Game *game)
{
    if (!is_empty_CyclicStack(game->history_field)) 
    {
        free_field(game, game->active_field);
        pop_CyclicStack(game->history_field, &(game->active_field));
    }
}

int start_event(Game *game, int event) 
{
    switch (event)
    {
        case TO_NEXT_GEN:
            if (to_next_gen(game) == MEMORY_REALLOCATION_ERROR) {
                return MEMORY_REALLOCATION_ERROR;
            }
            break;
        case TO_PREV_GEN:
            to_prev_gen(game);
            break;
        default:
        {
            return NON_EXISTENT_EVENT;
            break;
        }
    }
    return SUCCESS;
}

void render(Game *game)
{
    for (size_t i = 0; i < game->height; ++i)
    {
        printf("+");
        for (size_t j = 0; j < game->width; ++j) 
        {
            printf("-+");
        }
        printf("\n|");
        for (size_t j = 0; j < game->width; ++j) 
        {
            if (game->active_field->points[i][j] == true)
            {
                printf("▉|");
            } else
            {
                printf(" |");
            }
        }
        printf("\n");
    }
    printf("+");
    for (size_t j = 0; j < game->width; ++j) 
    {
        printf("-+");
    }
    printf("\n");
}

void free_game(Game *game)
{
    while (!is_empty_CyclicStack(game->history_field)) 
    {
        Field *field;
        pop_CyclicStack(game->history_field, &field);
        free_field(game, field);
    }
    free_field(game, game->active_field);
    free_CyclicStack(game->history_field);
}

int create_history(Game *game)
{
    if (init_CyclicStack(&(game->history_field), game->capacity, sizeof(Field *)) == MEMORY_REALLOCATION_ERROR)
    {
        return MEMORY_REALLOCATION_ERROR;
    }
    // for (size_t i = 0; i < game->capacity; ++i)
    // {
    //     Field *field = (Field *) malloc(sizeof(Field));
    //     field->points = NULL;
    //     push_CyclicStack(game->history_field, &field, NULL);
    // }
    return SUCCESS;
}

int start_game(size_t width, size_t height, size_t capacity)
{
    Game game = {width, height, capacity, NULL, NULL};
    if (create_history(&game) == MEMORY_REALLOCATION_ERROR)
    {
        return MEMORY_REALLOCATION_ERROR;
    }
    if (to_next_gen(&game) == MEMORY_REALLOCATION_ERROR)
    {
        free_CyclicStack(game.history_field);
        return MEMORY_REALLOCATION_ERROR;
    }
    if (input_points(&game, game.active_field) == EOF)
    {
        free_game(&game);
        return EOF;
    }
    int command;
    if (getchar() == EOF)
    {
        return EOF;
    }
    do
    {
        system("clear");
        render(&game);
        command = command_menu();
        if (command == EOF)
        {
            free_game(&game);
            return EOF;
        }
        if (command != EXIT) 
        {
            int result = start_event(&game, command);
            if (result != SUCCESS) 
            {
                return result;
            }
        }
    } while (command != EXIT);
    free_game(&game);
    return SUCCESS;
}