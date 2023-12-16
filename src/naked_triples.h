#pragma once

#include "sudoku.h"

typedef struct NakedTriple_impl {
    Cell *p_cells[3];
    int values[3];
} NakedTriple;

int find_naked_triples(Cell **p_cells, NakedTriple *naked_triples);
bool is_in_list_naked_triples(NakedTriple *p_array, int size, Cell **p_cells, int *values);
void find_naked_triples_in_group(Cell **p_group, NakedTriple *naked_triples, int *p_counter);
int naked_triples(SudokuBoard *p_board);