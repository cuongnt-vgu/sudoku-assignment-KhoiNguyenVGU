#pragma once

#include "sudoku.h"

typedef struct NakedTriples_impl
{
    Cell *p_cell_1;
    Cell *p_cell_2;
    Cell *p_cell_3;
} NakedTriples;

typedef struct UnsetDataTriples_impl
{
    Cell *p_cell;
    int candidate_1;
    int candidate_2;
    int candidate_3;
} UnsetDataTriples;

bool is_in_list_naked_triples(NakedTriples *p_array, Cell *p);
void find_naked_triples(Cell **p_cells, int *p_counter, int *p_unset, NakedTriples *p_naked_triples, UnsetDataTriples *p_unset_array);
int naked_triples(SudokuBoard *p_board);
