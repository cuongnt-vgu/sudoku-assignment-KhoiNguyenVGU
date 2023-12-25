#include "naked_pairs.h"

bool is_in_list_naked_pairs(NakedPairs *p_array, Cell *p)
{
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        if ((p_array[i].p_cell_1 == p) || (p_array[i].p_cell_2 == p))
        {
            return true;
        }
    }
    return false;
}

void find_naked_pairs(Cell **p_cells, int *p_counter, int *p_unset, NakedPairs *p_naked_pairs, UnsetDataPairs *p_unset_array)
{
    for (int i = 0; i < BOARD_SIZE - 1; i++)
    {
        if (p_cells[i]->num_candidates == 2)
        {
            for (int j = i + 1; j < BOARD_SIZE; j++)
            {
                if (p_cells[j]->num_candidates == 2)
                {
                    int *candidates_1 = get_candidates(p_cells[i]);
                    int *candidates_2 = get_candidates(p_cells[j]);
                    if ((candidates_1[0] == candidates_2[0]) && (candidates_1[1] == candidates_2[1]))
                    {
                        for (int k = 0; k < BOARD_SIZE; k++)
                        {
                            if ((k != i) && (k != j) && (p_cells[k]->num_candidates > 1))
                            {
                                if (!is_in_list_naked_pairs(p_naked_pairs, p_cells[k]))
                                {
                                    p_naked_pairs[*p_counter].p_cell_1 = p_cells[i];
                                    p_naked_pairs[*p_counter].p_cell_2 = p_cells[j];
                                    (*p_counter)++;
                                }

                                if (is_candidate(p_cells[k], candidates_1[0]) || is_candidate(p_cells[k], candidates_1[1]))
                                {
                                    p_unset_array[*p_unset].p_cell = p_cells[k];
                                    p_unset_array[*p_unset].candidate_1 = candidates_1[0];
                                    p_unset_array[*p_unset].candidate_2 = candidates_1[1];
                                    (*p_unset)++;
                                }
                            }
                        }
                    }
                    free(candidates_1);
                    free(candidates_2);
                }
            }
        }
    }
}

int naked_pairs(SudokuBoard *p_board)
{
    NakedPairs naked_pairs[BOARD_SIZE * BOARD_SIZE];
    int naked_pairs_counter = 0;
    UnsetDataPairs unset_array[BOARD_SIZE * BOARD_SIZE];
    int unset_counter = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs(p_board->p_rows[i], &naked_pairs_counter, &unset_counter, naked_pairs, unset_array);
        find_naked_pairs(p_board->p_cols[i], &naked_pairs_counter, &unset_counter, naked_pairs, unset_array);
        find_naked_pairs(p_board->p_boxes[i], &naked_pairs_counter, &unset_counter, naked_pairs, unset_array);
    }

    for (int i = 0; i < unset_counter; i++)
    {
        if (is_candidate(unset_array[i].p_cell, unset_array[i].candidate_1))
        {
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_1);
        }
        if (is_candidate(unset_array[i].p_cell, unset_array[i].candidate_2))
        {
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_2);
        }
    }
    
    return naked_pairs_counter;
}