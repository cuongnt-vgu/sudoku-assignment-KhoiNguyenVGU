#include "naked_triples.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool is_in_list_naked_triples(NakedTriples *p_array, Cell *p) 
{
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) 
    {
        if ((p_array[i].p_cell_1 == p) || (p_array[i].p_cell_2 == p) || (p_array[i].p_cell_3 == p)) 
        {
            return true;
        }
    }
    return false;
}

void find_naked_triples(Cell **p_cells, int *p_counter, int *p_unset, NakedTriples *p_naked_triples, UnsetDataTriples *p_unset_array) 
{
    for (int i = 0; i < BOARD_SIZE - 2; i++) 
    {
        if (p_cells[i]->num_candidates == 2 || p_cells[i]->num_candidates == 3) 
        {
            for (int j = i + 1; j < BOARD_SIZE - 1; j++) 
            {
                if (p_cells[j]->num_candidates == 2 || p_cells[j]->num_candidates == 3) 
                {
                    for (int k = j + 1; k < BOARD_SIZE; k++) 
                    {
                        if (p_cells[k]->num_candidates == 2 || p_cells[k]->num_candidates == 3) 
                        {
                            int *candidates_1 = get_candidates(p_cells[i]);
                            int *candidates_2 = get_candidates(p_cells[j]);
                            int *candidates_3 = get_candidates(p_cells[k]);
                            int *unique_candidates = unique_candidates_arr(p_cells[i], p_cells[j], p_cells[k], p_cells[i]->num_candidates, p_cells[j]->num_candidates, p_cells[k]->num_candidates);

                            if (num_unique_candidates(p_cells[i], p_cells[j], p_cells[k], p_cells[i]->num_candidates, p_cells[j]->num_candidates, p_cells[k]->num_candidates) == 3)
                            {    
                                for (int l = 0; l < BOARD_SIZE; l++) 
                                {
                                    if ((l != i) && (l != j) && (l != k) && (p_cells[l]->num_candidates > 1)) 
                                    {
                                        if (!is_in_list_naked_triples(p_naked_triples, p_cells[l])) 
                                        {
                                            p_naked_triples[*p_counter].p_cell_1 = p_cells[i];
                                            p_naked_triples[*p_counter].p_cell_2 = p_cells[j];
                                            p_naked_triples[*p_counter].p_cell_3 = p_cells[k];
                                            (*p_counter)++;
                                        }

                                        if (is_candidate(p_cells[l], unique_candidates[0]) || is_candidate(p_cells[l], unique_candidates[1]) || is_candidate(p_cells[l], unique_candidates[2])) 
                                        {
                                            p_unset_array[*p_unset].p_cell = p_cells[l];
                                            p_unset_array[*p_unset].candidate_1 = unique_candidates[0];
                                            p_unset_array[*p_unset].candidate_2 = unique_candidates[1];
                                            p_unset_array[*p_unset].candidate_3 = unique_candidates[2];
                                            (*p_unset)++;
                                        }
                                    }
                                }
                            }
                            free(candidates_1);
                            free(candidates_2);
                            free(candidates_3);
                            free(unique_candidates);
                        }
                    }
                }
            }
        }
    }
}

int num_unique_candidates(Cell *cell_1, Cell *cell_2, Cell *cell_3, int len_1, int len_2, int len_3)
{
    int *candidates_1 = get_candidates(cell_1);
    int *candidates_2 = get_candidates(cell_2);
    int *candidates_3 = get_candidates(cell_3);

    int unique_candidates[3];
    int count = 0;

    for (int i = 0; i < len_1; i++) 
    {
        if (!is_in_array(unique_candidates, count, candidates_1[i])) 
        {
            unique_candidates[count++] = candidates_1[i];
        }
    }
    
    for (int i = 0; i < len_2; i++) 
    {
        if (!is_in_array(unique_candidates, count, candidates_2[i])) 
        {
            unique_candidates[count++] = candidates_2[i];
        }
    }
    
    for (int i = 0; i < len_3; i++) 
    {
        if (!is_in_array(unique_candidates, count, candidates_3[i])) 
        {
            unique_candidates[count++] = candidates_3[i];
        }
    }

    return count;
}

int *unique_candidates_arr(Cell *cell_1, Cell *cell_2, Cell *cell_3, int len_1, int len_2, int len_3)
{
    int *candidates_1 = get_candidates(cell_1);
    int *candidates_2 = get_candidates(cell_2);
    int *candidates_3 = get_candidates(cell_3);

    int *unique_candidates = malloc(3 * sizeof(int));
    int count = 0;

    for (int i = 0; i < len_1; i++) 
    {
        if (!is_in_array(unique_candidates, count, candidates_1[i])) 
        {
            unique_candidates[count++] = candidates_1[i];
        }
    }
    
    for (int i = 0; i < len_2; i++) 
    {
        if (!is_in_array(unique_candidates, count, candidates_2[i])) 
        {
            unique_candidates[count++] = candidates_2[i];
        }
    }
    
    for (int i = 0; i < len_3; i++) 
    {
        if (!is_in_array(unique_candidates, count, candidates_3[i])) 
        {
            unique_candidates[count++] = candidates_3[i];
        }
    }

    return unique_candidates;
}

int is_in_array(int *array, int count, int value) 
{
    for (int i = 0; i < count; i++) 
    {
        if (array[i] == value) 
        {
            return 1;
        }
    }
    return 0;
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
        }
        if (is_candidate(unset_array[i].p_cell, unset_array[i].candidate_2)) 
        {
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_2);
        }
        if (is_candidate(unset_array[i].p_cell, unset_array[i].candidate_3)) 
        {
            unset_candidate(unset_array[i].p_cell, unset_array[i].candidate_3);
        }
    }

    return triples_counter;
}