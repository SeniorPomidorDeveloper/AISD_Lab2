#ifndef GAME_H
#define GAME_H

#include <stddef.h>
#include <stdbool.h>

#include "libs/CyclicStack/CyclicStack.h"

#define LEN_BUF_LIVE_POINT 10

enum game_errors_code
{
    SUCCESS,
    COORDINATE_ERROR,
    NON_EXISTENT_EVENT
};

enum game_commands_code
{
    EXIT,
    TO_NEXT_GEN,
    TO_PREV_GEN,
    INVALID_COMMAND
};

typedef struct Point
{
    size_t x;
    size_t y;
} Point;

typedef struct Field
{
    bool **points;
} Field;

typedef struct Game
{
    size_t width;
    size_t height;
    size_t capacity;
    Field *active_field;
    CyclicStack *history_field;
} Game;

int init_field(Game *game, Field *field);   // Инициализация игрового поля.
void free_field(Game *game, Field *field);  // Отчистка памяти отведённого под игровое поле.

int create_new_point(Game *game, Field *field, Point *point); // Создание новой живой точки на игровом поле на котором игрок находится в данный момен времени.
unsigned short int count_neighbours(Game *game, Field *field, Point *point); 
void generate_new_points(Game *game, Field *field); // Создание следующего поколения точек на игровом поле. 
int to_next_gen(Game *game);                    // Переход к следующему поколению живых точек на игровом поле.
void to_prev_gen(Game *game);                    // Переход к предыдущему поколению живых точек на игровом поле. 

void free_game(Game *game); // Освобождение памяти, выделенной за время игры.
int start_event(Game *game, int event); // Обработка событий.
int create_history(Game *game); // Создание истории живых точек на игровом поле.

void render(Game *game); // Рендер игрового поля на экране.
int input_points(Game *game, Field *field); // Ввод живых точек на игровом поле.
void print_menu(); // Вывод меню ввода команд.
int command_menu(); // Меню ввода комманд.

int start_game(size_t width, size_t height, size_t capacity); // Запуск игры.

#endif // GAME_H