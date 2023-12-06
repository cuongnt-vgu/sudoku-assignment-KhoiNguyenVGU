#include "hidden_pairs.h"
#include "sudoku.h"

// Helper function to find hidden pairs in a group of cells
void find_hidden_pairs(Cell **p_cells, int *hidden_pair_values, int *pair_count)
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
                    // Found a hidden pair
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

                    // Record the hidden pair values
                    hidden_pair_values[(*pair_count)++] = candidate1;
                    hidden_pair_values[(*pair_count)++] = candidate2;
                }
            }
        }
    }
}

// Function to apply the hidden pairs technique to a Sudoku board
int hidden_pairs(SudokuBoard *p_board)
{
    int pair_count = 0;
    int hidden_pair_values[BOARD_SIZE * 2];  // Assuming pairs can be found in one row/column/box

    // Check hidden pairs in rows
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        find_hidden_pairs(p_board->p_rows[i], hidden_pair_values, &pair_count);
    }

    // Check hidden pairs in columns
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        find_hidden_pairs(p_board->p_cols[i], hidden_pair_values, &pair_count);
    }

    // Check hidden pairs in boxes
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        find_hidden_pairs(p_board->p_boxes[i], hidden_pair_values, &pair_count);
    }

    // Apply the hidden pairs
    // Implement the logic to eliminate hidden pair candidates from other cells

    return pair_count;
}