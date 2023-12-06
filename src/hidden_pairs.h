#pragma once
#include "sudoku.h"

// Define any constants or types specific to hidden pairs

// Function declarations
void find_hidden_pairs(Cell **p_cells, int *hidden_pair_values, int *pair_count);
int hidden_pairs(SudokuBoard *p_board);