#pragma once

#include "sudoku.h"

typedef struct HiddenTriple_impl {
    Cell *p_cells[3];
    int values[3];
} HiddenTriple;

int find_hidden_triples(Cell **p_cells, HiddenTriple *hidden_triples);
bool is_in_list_hidden_triples(HiddenTriple *p_array, int size, Cell **p_cells, int *values);
void find_hidden_triples_in_group(Cell **p_group, HiddenTriple *hidden_triples, int *p_counter);
int hidden_triples(SudokuBoard *p_board);