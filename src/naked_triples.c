#include "naked_triples.h"

bool is_in_list_naked_triples(NakedTriples *p_array, Cell *p, Cell *m, Cell *n) 
{
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) 
    {
        if ((p_array[i].p_cell_1 == p) && (p_array[i].p_cell_2 == m) && (p_array[i].p_cell_3 == n))
        {
            return true;
        }
    }
    return false;
}

void find_naked_triples(Cell **p_cells, int *p_counter, int *p_unset, NakedTriples *p_naked_triples, UnsetDataTriples *p_unset_array) 
{
    int candidate_count[BOARD_SIZE] = {0};

    int diff_count = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        int *candidates = get_candidates(p_cells[i]);
        for (int j = 0; j < p_cells[i]->num_candidates; j++)
        {
            candidate_count[candidates[j] - 1]++;
        }

        free(candidates);
    }
    
    int saved_candidates[BOARD_SIZE];
    int saved_counter = 0;
    
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        if (candidate_count[i] == 2 || candidate_count[i] == 3)
        {
            saved_candidates[saved_counter++] = i + 1;
        }
    }

    if (saved_counter < 3)
    {
        return;
    }

    int stored_candidates[3] = {0};

    for (int i = 0; i < BOARD_SIZE - 2; i++)
    {
        for (int j = i + 1; j < BOARD_SIZE - 1; j++)
        {
            for (int k = j + 1; k < BOARD_SIZE; k++)
            {   
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_cells[l]->num_candidates > 1)
                    {   
                        int *candidates_l = get_candidates(p_cells[l]);
                        
                        for (int m = 0; m < p_cells[l]->num_candidates; m++)
                        {
                            if (!is_in_candidates(saved_candidates, candidates_l[m]))
                            {
                                diff_count++;
                            }
                        }

                        free(candidates_l);

                        if (diff_count == 0)
                        {
                            for (int n = 0; n < BOARD_SIZE; n++)
                            {
                                if (p_cells[n]->num_candidates > 1)
                                {   
                                    int *candidates_n = get_candidates(p_cells[n]);
                                    
                                    for (int o = 0; o < p_cells[n]->num_candidates; o++)
                                    {
                                        if (!is_in_candidates(saved_candidates, candidates_n[o]))
                                        {
                                            diff_count++;
                                        }
                                    }

                                    free(candidates_n);

                                    if (diff_count == 0)
                                    {
                                        for (int p = 0; p < BOARD_SIZE; p++)
                                        {
                                            if (p_cells[p]->num_candidates > 1)
                                            {   
                                                int *candidates_p = get_candidates(p_cells[p]);
                                                
                                                for (int q = 0; q < p_cells[p]->num_candidates; q++)
                                                {
                                                    if (!is_in_candidates(saved_candidates, candidates_p[q]))
                                                    {
                                                        diff_count++;
                                                    }
                                                }

                                                free(candidates_p);

                                                if (diff_count == 0)
                                                {                       
                                                    if (!is_in_list_naked_triples(p_naked_triples, p_cells[l], p_cells[n], p_cells[p]))
                                                    {
                                                        p_naked_triples[*p_counter].p_cell_1 = p_cells[l];
                                                        p_naked_triples[*p_counter].p_cell_2 = p_cells[n];
                                                        p_naked_triples[*p_counter].p_cell_3 = p_cells[p];
                                                        (*p_counter)++;
                                                    }

                                                    for (int r = 0; r < BOARD_SIZE; r++)
                                                    {
                                                        if(p_cells[r] != p_cells[l] && p_cells[r] != p_cells[n] && p_cells[r] != p_cells[p])
                                                        {
                                                            if (is_candidate(p_cells[r], stored_candidates[0]))
                                                            {
                                                                p_unset_array[*p_unset].p_cell = p_cells[r];
                                                                p_unset_array[*p_unset].candidate_1 = stored_candidates[0];
                                                                p_unset_array[*p_unset].candidate_2 = stored_candidates[1];
                                                                p_unset_array[*p_unset].candidate_3 = stored_candidates[2];
                                                                (*p_unset)++;
                                                            }

                                                            if (is_candidate(p_cells[r], stored_candidates[1]))
                                                            {
                                                                p_unset_array[*p_unset].p_cell = p_cells[r];
                                                                p_unset_array[*p_unset].candidate_1 = stored_candidates[0];
                                                                p_unset_array[*p_unset].candidate_2 = stored_candidates[1];
                                                                p_unset_array[*p_unset].candidate_3 = stored_candidates[2];
                                                                (*p_unset)++;
                                                            }

                                                            if (is_candidate(p_cells[r], stored_candidates[2]))
                                                            {
                                                                p_unset_array[*p_unset].p_cell = p_cells[r];
                                                                p_unset_array[*p_unset].candidate_1 = stored_candidates[0];
                                                                p_unset_array[*p_unset].candidate_2 = stored_candidates[1];
                                                                p_unset_array[*p_unset].candidate_3 = stored_candidates[2];
                                                                (*p_unset)++;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool is_in_candidates(int *stored, int candidate)
{
    for (int i = 0; i < 3; i++)
    {
        if (stored[i] == candidate)
            return true;
    }

    return false;
}

int naked_triples(SudokuBoard *p_board) 
{
    NakedTriples naked_triples[BOARD_SIZE * BOARD_SIZE];
    int triples_counter = 0;
    UnsetDataTriples unset_array[BOARD_SIZE * BOARD_SIZE];
    int unset_counter = 0;

    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        find_naked_triples(p_board->p_rows[i], &triples_counter, &unset_counter, naked_triples, unset_array);
        find_naked_triples(p_board->p_cols[i], &triples_counter, &unset_counter, naked_triples, unset_array);
        find_naked_triples(p_board->p_boxes[i], &triples_counter, &unset_counter, naked_triples, unset_array);
    }

    for (int i = 0; i < unset_counter; i++) 
    {
        if (is_candidate(unset_array[i].p_cell, unset_array[i].candidate_1)) 
        {
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_1);
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_2);
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_3);
        }
        if (is_candidate(unset_array[i].p_cell, unset_array[i].candidate_2)) 
        {
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_1);
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_2);
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_3);
        }
        if (is_candidate(unset_array[i].p_cell, unset_array[i].candidate_3)) 
        {
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_1);
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_2);
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_3);
        }
    }

    return triples_counter;
}