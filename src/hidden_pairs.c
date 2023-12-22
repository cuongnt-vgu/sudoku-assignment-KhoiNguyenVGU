#include "hidden_pairs.h"

bool is_in_cell_pairs(Cell **p_cells, int value_1, int value_2)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if ((p_cells[i]->candidates[value_1 - 1] == 1 && p_cells[i]->candidates[value_2 - 1] != 1) || (p_cells[i]->candidates[value_2 - 1] == 1 && p_cells[i]->candidates[value_1 - 1] != 1))
        {
            return false;
        }
    }
    return true;
}

int find_hidden_pairs_values(Cell **p_cells, int *hidden_pair_values)
{
    int counter = 0;
    int candidates_counter[BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        candidates_counter[i] = 0;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->num_candidates > 1)
        {
            int *candidates = get_candidates(p_cells[i]);
            for (int j = 0; j < p_cells[i]->num_candidates; j++)
            {
                candidates_counter[candidates[j] - 1]++;
            }
            free(candidates);
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (candidates_counter[i] == 2)
        {
            hidden_pair_values[counter++] = i + 1;
        }
    }
    return counter;
}

void find_hidden_pairs(Cell **p_cells, HiddenPairs *p_hidden_pairs, int *p_counter)
{
    int hidden_pair_values[BOARD_SIZE];
    int counter = find_hidden_pairs_values(p_cells, hidden_pair_values);

    for (int i = 0; i < counter - 1; i++)
    {
        for (int j = i + 1; j < counter; j++)
        {
            if (is_in_cell_pairs(p_cells, hidden_pair_values[i], hidden_pair_values[j]))
            {
                for (int k = 0; k < BOARD_SIZE - 1; k++)
                {
                    for (int l = k + 1; l < BOARD_SIZE; l++)
                    {
                        if (p_cells[k]->candidates[hidden_pair_values[i] - 1] == 1 && p_cells[k]->candidates[hidden_pair_values[j] - 1] == 1 && p_cells[l]->candidates[hidden_pair_values[i] - 1] == 1 && p_cells[l]->candidates[hidden_pair_values[j] - 1] == 1)
                        {
                            p_hidden_pairs[(*p_counter)++] = (HiddenPairs){p_cells[k], p_cells[l], hidden_pair_values[i], hidden_pair_values[j]};
                        }
                    }
                }
            }
        }
    }
}

int hidden_pairs(SudokuBoard *p_board) 
{
    int pair_count = 0;
    int same_pair_count = 0;
    HiddenPairs hidden_pairs[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {   
        find_hidden_pairs(p_board->p_rows[i], hidden_pairs, &pair_count);
        find_hidden_pairs(p_board->p_cols[i], hidden_pairs, &pair_count);
        find_hidden_pairs(p_board->p_boxes[i], hidden_pairs, &pair_count);
    }

    for (int i = 0; i < pair_count; i++)
    {
        if (hidden_pairs[i].p_cell_1->num_candidates == 2 && hidden_pairs[i].p_cell_2->num_candidates == 2)
        {
            same_pair_count++;
        }
        
        int num_1 = hidden_pairs[i].p_cell_1->num_candidates;
        int num_2 = hidden_pairs[i].p_cell_2->num_candidates;
        int *candidates_1 = get_candidates(hidden_pairs[i].p_cell_1);
        int *candidates_2 = get_candidates(hidden_pairs[i].p_cell_2);

        for (int j = 0; j < num_1; j++)
        {
            if (candidates_1[j] != hidden_pairs[i].candidate_1 && candidates_1[j] != hidden_pairs[i].candidate_2)
            {
                unset_candidate(hidden_pairs[i].p_cell_1, candidates_1[j]);
            }
        }

        for (int j = 0; j < num_2; j++)
        {
            if (candidates_2[j] != hidden_pairs[i].candidate_1 && candidates_2[j] != hidden_pairs[i].candidate_2)
            {
                unset_candidate(hidden_pairs[i].p_cell_2, candidates_2[j]);
            }
        }

        free(candidates_1);
        free(candidates_2);
    }

    return pair_count - same_pair_count;
}