#pragma once

#include "sudoku.h"

typedef struct HiddenSingle_impl
{
    Cell *p_cell;
    int value;
} HiddenSingle;

int find_hidden_single_values(Cell **p_cells, int *hidden_single_values);

bool is_in_list_hidden_singles(HiddenSingle *p_array, int size, Cell *p);

void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter);

int hidden_singles(SudokuBoard *p_board);