#include "hidden_triples.h"

bool is_in_cell_triples(Cell **p_cells, int num_1, int num_2, int num_3)
{
    int counter = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->candidates[num_1 - 1] == 1 || p_cells[i]->candidates[num_2 - 1] == 1 || p_cells[i]->candidates[num_3 - 1] == 1)
        {
            counter++;
        }
    }

    return counter == 3;
}

int find_hidden_triple_values(Cell **p_cells, int *hidden_triple_values)
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
        if (candidates_counter[i] == 2 || candidates_counter[i] == 3)
        {
            hidden_triple_values[counter++] = i + 1;
        }
    }
    return counter;
}

void find_hidden_triples(Cell **p_cells, HiddenTriples *p_hidden_triples, int *p_counter)
{
    int hidden_triple_values[BOARD_SIZE];
    int counter = find_hidden_triple_values(p_cells, hidden_triple_values);

    for (int i = 0; i < counter - 2; i++)
    {
        for (int j = i + 1; j < counter - 1; j++)
        {
            for (int k = j + 1; k < counter; k++)
            {
                if (is_in_cell_triples(p_cells, hidden_triple_values[i], hidden_triple_values[j], hidden_triple_values[k]))
                {
                    for (int l = 0; l < BOARD_SIZE - 2; l++)
                    {
                        for (int m = l + 1; m < BOARD_SIZE - 1; m++)
                        {
                            for (int n = m + 1; n < BOARD_SIZE; n++)
                            {
                                int count_l = 0;
                                if (p_cells[l]->candidates[hidden_triple_values[i] - 1] > 0) count_l++;
                                if (p_cells[l]->candidates[hidden_triple_values[j] - 1] > 0) count_l++;
                                if (p_cells[l]->candidates[hidden_triple_values[k] - 1] > 0) count_l++;

                                int count_m = 0;
                                if (p_cells[m]->candidates[hidden_triple_values[i] - 1] > 0) count_m++;
                                if (p_cells[m]->candidates[hidden_triple_values[j] - 1] > 0) count_m++;
                                if (p_cells[m]->candidates[hidden_triple_values[k] - 1] > 0) count_m++;

                                int count_n = 0;
                                if (p_cells[n]->candidates[hidden_triple_values[i] - 1] > 0) count_n++;
                                if (p_cells[n]->candidates[hidden_triple_values[j] - 1] > 0) count_n++;
                                if (p_cells[n]->candidates[hidden_triple_values[k] - 1] > 0) count_n++;

                                if (count_l > 1 && count_m > 1 && count_n > 1)
                                {
                                    p_hidden_triples[(*p_counter)++] = (HiddenTriples){p_cells[l], p_cells[m], p_cells[n], hidden_triple_values[i], hidden_triple_values[j], hidden_triple_values[k]};
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int hidden_triples(SudokuBoard *p_board) {
    int triple_count = 0;
    int same_triple_count = 0;
    HiddenTriples hidden_triples[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {   
        find_hidden_triples(p_board->p_rows[i], hidden_triples, &triple_count);
        find_hidden_triples(p_board->p_cols[i], hidden_triples, &triple_count);
        find_hidden_triples(p_board->p_boxes[i], hidden_triples, &triple_count);
    }

    for (int i = 0; i < triple_count; i++)
    {   
        if ((hidden_triples[i].p_cell_1->num_candidates == 2 || hidden_triples[i].p_cell_1->num_candidates == 3) && (hidden_triples[i].p_cell_2->num_candidates == 2 || hidden_triples[i].p_cell_2->num_candidates == 3) && (hidden_triples[i].p_cell_3->num_candidates == 2 || hidden_triples[i].p_cell_3->num_candidates == 3))
        {
            same_triple_count++;
        }
        int num_1 = hidden_triples[i].p_cell_1->num_candidates;
        int num_2 = hidden_triples[i].p_cell_2->num_candidates;
        int num_3 = hidden_triples[i].p_cell_3->num_candidates;
        int *candidates_1 = get_candidates(hidden_triples[i].p_cell_1);
        int *candidates_2 = get_candidates(hidden_triples[i].p_cell_2);
        int *candidates_3 = get_candidates(hidden_triples[i].p_cell_3);

        for (int j = 0; j < num_1; j++)
        {
            if (candidates_1[j] != hidden_triples[i].candidate_1 && candidates_1[j] != hidden_triples[i].candidate_2 && candidates_1[j] != hidden_triples[i].candidate_3)
            {
                unset_candidate(hidden_triples[i].p_cell_1, candidates_1[j]);
            }
        }

        for (int j = 0; j < num_2; j++)
        {
            if (candidates_2[j] != hidden_triples[i].candidate_1 && candidates_2[j] != hidden_triples[i].candidate_2 && candidates_2[j] != hidden_triples[i].candidate_3)
            {
                unset_candidate(hidden_triples[i].p_cell_2, candidates_2[j]);
            }
        }

        for (int j = 0; j < num_3; j++)
        {
            if (candidates_3[j] != hidden_triples[i].candidate_1 && candidates_3[j] != hidden_triples[i].candidate_2 && candidates_3[j] != hidden_triples[i].candidate_3)
            {
                unset_candidate(hidden_triples[i].p_cell_3, candidates_3[j]);
            }
        }

        free(candidates_1);
        free(candidates_2);
        free(candidates_3);
    }

    return triple_count - same_triple_count;
}