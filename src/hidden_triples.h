#pragma once

#include "sudoku.h"

typedef struct HiddenTriple_impl
{
    Cell *p_cell_1;
    Cell *p_cell_2;
    Cell *p_cell_3;  
    int candidate_1;     
    int candidate_2;     
    int candidate_3;     
} HiddenTriple;

bool is_in_cell_triples(Cell **p_cells, int num_1, int num_2, int num_3);
int find_hidden_triple_values(Cell **p_cells, int *hidden_triple_values);
void find_hidden_triple(Cell **p_cells, HiddenTriple *p_hidden_triples, int *p_counter);
int hidden_triples(SudokuBoard *p_board);