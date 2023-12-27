#pragma once

#include "sudoku.h"

typedef struct NakedTriples_struct
{
    Cell **p_cells;
    int index[3];
    int value[3];
} NakedTriples;

int check_naked_triples(Cell **p_cells, int *triples, int *index);
void find_naked_triples(Cell **p_cells, NakedTriples *p_naked_triples, int *p_counter, int unit);
int naked_triples(SudokuBoard *p_board);