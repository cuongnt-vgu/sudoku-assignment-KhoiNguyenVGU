#include "naked_pairs.h"
#include "sudoku.h"

// Helper function to find naked pairs in a group of cells
void find_naked_pairs(Cell **p_cells, int *naked_pair_values, int *pair_count)
{
    // Iterate over each pair of cells
    for (int i = 0; i < BOARD_SIZE - 1; ++i)
    {
        for (int j = i + 1; j < BOARD_SIZE; ++j)
        {
            // Check if both cells have exactly two candidates
            if (p_cells[i]->num_candidates == 2 && p_cells[j]->num_candidates == 2)
            {
                // Check if the candidates in both cells are the same
                if (p_cells[i]->candidates[0] == p_cells[j]->candidates[0] &&
                    p_cells[i]->candidates[1] == p_cells[j]->candidates[1])
                {
                    // Found a naked pair
                    int candidate1 = p_cells[i]->candidates[0];
                    int candidate2 = p_cells[i]->candidates[1];

                    // Update candidates in other cells of the group
                    for (int k = 0; k < BOARD_SIZE; ++k)
                    {
                        if (k != i && k != j)
                        {
                            unset_candidate(p_cells[k], candidate1);
                            unset_candidate(p_cells[k], candidate2);
                        }
                    }

                    // Record the naked pair values
                    naked_pair_values[(*pair_count)++] = candidate1;
                    naked_pair_values[(*pair_count)++] = candidate2;
                }
            }
        }
    }
}

// Function to apply the naked pairs technique to a Sudoku board
int naked_pairs(SudokuBoard *p_board)
{
    int pair_count = 0;
    int naked_pair_values[BOARD_SIZE * 2];  // Assuming pairs can be found in one row/column/box

    // Check naked pairs in rows
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        find_naked_pairs(p_board->p_rows[i], naked_pair_values, &pair_count);
    }

    // Check naked pairs in columns
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        find_naked_pairs(p_board->p_cols[i], naked_pair_values, &pair_count);
    }

    // Check naked pairs in boxes
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        find_naked_pairs(p_board->p_boxes[i], naked_pair_values, &pair_count);
    }

    // Apply the naked pairs
    // Implement the logic to eliminate naked pair candidates from other cells

    return pair_count;
}