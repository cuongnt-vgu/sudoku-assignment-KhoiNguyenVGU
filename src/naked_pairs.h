#pragma once
#include "sudoku.h"

// Function declarations
void find_naked_pairs(Cell **p_cells, int *naked_pair_values, int *pair_count);
int naked_pairs(SudokuBoard *p_board);