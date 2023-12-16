#pragma once

#include "sudoku.h"

typedef struct HiddenPair_impl {
    Cell *p_cells[2];
    int values[2];
} HiddenPair;

int find_hidden_pairs(Cell **p_cells, HiddenPair *hidden_pairs);
bool is_in_list_hidden_pairs(HiddenPair *p_array, int size, Cell **p_cells, int *values);
void find_hidden_pairs_in_group(Cell **p_group, HiddenPair *hidden_pairs, int *p_counter);
int hidden_pairs(SudokuBoard *p_board);