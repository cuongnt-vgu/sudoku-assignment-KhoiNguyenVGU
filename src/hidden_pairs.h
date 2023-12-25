#pragma once

#include "sudoku.h"

typedef struct HiddenPairs_struct
{
    Cell *p_cell_1;
    Cell *p_cell_2;
    int candidate_1;    
    int candidate_2;   
} HiddenPairs;

int find_hidden_pairs_values(Cell **p_cells, int *hidden_pair_values);
void find_hidden_pairs(Cell **p_cells, HiddenPairs *p_hidden_pairs, int *p_counter);
int hidden_pairs(SudokuBoard *p_board);