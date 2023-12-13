#pragma once

#include "sudoku.h"

// Function prototypes
int check_triple(SudokuBoard *p_board, int row1, int col1, int row2, int col2);
int contains(int *array, int size, int value);
void remove_other_candidates(SudokuBoard *p_board, int row1, int col1, int row2, int col2, int *candidates, int num_candidates);

int naked_triples(SudokuBoard *p_board);