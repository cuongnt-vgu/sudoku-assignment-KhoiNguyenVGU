#pragma once

#include "sudoku.h"

typedef struct NakedPair_impl {
    Cell *p_cells[2];
    int values[2];
} NakedPair;

int find_naked_pairs(Cell **p_cells, NakedPair *naked_pairs);
bool is_in_list_naked_pairs(NakedPair *p_array, int size, Cell **p_cells, int *values);
void find_naked_pairs_in_group(Cell **p_group, NakedPair *naked_pairs, int *p_counter);
int naked_pairs(SudokuBoard *p_board);