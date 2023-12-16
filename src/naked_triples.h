#pragma once

#include "sudoku.h"

typedef struct NakedTriple_impl
{
    Cell *p_cells[3];
    int values[3];
} NakedTriple;

int find_naked_triples_in_group(Cell **p_cells, NakedTriple *naked_triples, int *p_counter);
void remove_naked_triple_candidates(Cell **p_cells, NakedTriple naked_triple);
int naked_triples(SudokuBoard *p_board);