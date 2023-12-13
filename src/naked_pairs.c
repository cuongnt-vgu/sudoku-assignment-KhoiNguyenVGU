#include "naked_pairs.h"
#include "utils.h"

int naked_pairs(SudokuBoard *p_board)
{
    int pairs_found = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cell *cell = &p_board->data[i][j];
            if (cell->num_candidates != 2)
                continue;

            // Check row
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                if (k == j)
                    continue;
                Cell *other_cell = &p_board->data[i][k];
                if (other_cell->num_candidates != 2)
                    continue;
                if (is_candidate(cell, other_cell->candidates[0]) && is_candidate(cell, other_cell->candidates[1]))
                {
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (l == j || l == k)
                            continue;
                        unset_candidate(&p_board->data[i][l], other_cell->candidates[0]);
                        unset_candidate(&p_board->data[i][l], other_cell->candidates[1]);
                    }
                    pairs_found++;
                }
            }

            // Check column
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                if (k == i)
                    continue;
                Cell *other_cell = &p_board->data[k][j];
                if (other_cell->num_candidates != 2)
                    continue;
                if (is_candidate(cell, other_cell->candidates[0]) && is_candidate(cell, other_cell->candidates[1]))
                {
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (l == i || l == k)
                            continue;
                        unset_candidate(&p_board->data[l][j], other_cell->candidates[0]);
                        unset_candidate(&p_board->data[l][j], other_cell->candidates[1]);
                    }
                    pairs_found++;
                }
            }

            // Check block
            int start_row = (i / 3) * 3;
            int start_col = (j / 3) * 3;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (start_row + k == i && start_col + l == j)
                        continue;
                    Cell *other_cell = &p_board->data[start_row + k][start_col + l];
                    if (other_cell->num_candidates != 2)
                        continue;
                    if (is_candidate(cell, other_cell->candidates[0]) && is_candidate(cell, other_cell->candidates[1]))
                    {
                        for (int m = 0; m < 3; m++)
                        {
                            for (int n = 0; n < 3; n++)
                            {
                                if ((start_row + m == i && start_col + n == j) || (start_row + m == start_row + k && start_col + n == start_col + l))
                                    continue;
                                unset_candidate(&p_board->data[start_row + m][start_col + n], other_cell->candidates[0]);
                                unset_candidate(&p_board->data[start_row + m][start_col + n], other_cell->candidates[1]);
                            }
                        }
                        pairs_found++;
                    }
                }
            }
        }
    }

    return pairs_found;
}