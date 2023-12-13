#include <stdlib.h>
#include "hidden_pairs.h"
#include "utils.h"

int hidden_pairs(SudokuBoard *p_board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int num1 = 1; num1 <= BOARD_SIZE; num1++)
        {
            for (int num2 = num1 + 1; num2 <= BOARD_SIZE; num2++)
            {
                Cell *pair_cells[2] = {NULL, NULL};
                int pair_count;

                // Check rows
                pair_count = 0;
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    Cell *cell = p_board->p_rows[i][j];
                    if (is_candidate(cell, num1) && is_candidate(cell, num2))
                    {
                        pair_cells[pair_count++] = cell;
                        if (pair_count > 2)
                            break;
                    }
                }

                if (pair_count == 2 && pair_cells[0]->num_candidates > 2 && pair_cells[1]->num_candidates > 2)
                {
                    for (int num = 1; num <= BOARD_SIZE; num++)
                    {
                        if (num != num1 && num != num2)
                        {
                            unset_candidate(pair_cells[0], num);
                            unset_candidate(pair_cells[1], num);
                        }
                    }
                    return 1;
                }

                // Check columns
                pair_count = 0;
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    Cell *cell = p_board->p_cols[i][j];
                    if (is_candidate(cell, num1) && is_candidate(cell, num2))
                    {
                        pair_cells[pair_count++] = cell;
                        if (pair_count > 2)
                            break;
                    }
                }

                if (pair_count == 2 && pair_cells[0]->num_candidates > 2 && pair_cells[1]->num_candidates > 2)
                {
                    for (int num = 1; num <= BOARD_SIZE; num++)
                    {
                        if (num != num1 && num != num2)
                        {
                            unset_candidate(pair_cells[0], num);
                            unset_candidate(pair_cells[1], num);
                        }
                    }
                    return 1;
                }

                // Check boxes
                pair_count = 0;
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    Cell *cell = p_board->p_boxes[i][j];
                    if (is_candidate(cell, num1) && is_candidate(cell, num2))
                    {
                        pair_cells[pair_count++] = cell;
                        if (pair_count > 2)
                            break;
                    }
                }

                if (pair_count == 2 && pair_cells[0]->num_candidates > 2 && pair_cells[1]->num_candidates > 2)
                {
                    for (int num = 1; num <= BOARD_SIZE; num++)
                    {
                        if (num != num1 && num != num2)
                        {
                            unset_candidate(pair_cells[0], num);
                            unset_candidate(pair_cells[1], num);
                        }
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}