#pragma once

#include "sudoku.h"

typedef struct HiddenTriples_struct
{
    Cell *p_cell_1;
    Cell *p_cell_2;
    Cell *p_cell_3;  
    int candidate_1;     
    int candidate_2;     
    int candidate_3;     
} HiddenTriples;

int find_hidden_triple_values(Cell **p_cells, int *hidden_triple_values);
void find_hidden_triple(Cell **p_cells, HiddenTriples *p_hidden_triples, int *p_counter);
int hidden_triples(SudokuBoard *p_board);