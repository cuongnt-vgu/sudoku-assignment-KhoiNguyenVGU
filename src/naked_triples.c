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
        if (p_cells[i]->num_candidates == 3) 
        {
            for (int j = i + 1; j < BOARD_SIZE - 1; j++) 
            {
                if (p_cells[j]->num_candidates == 3) 
                {
                    for (int k = j + 1; k < BOARD_SIZE; k++) 
                    {
                        if (p_cells[k]->num_candidates == 3) 
                        {
                            int *candidates_1 = get_candidates(p_cells[i]);
                            int *candidates_2 = get_candidates(p_cells[j]);
                            int *candidates_3 = get_candidates(p_cells[k]);
                            
                            if ((candidates_1[0] == candidates_2[0] && candidates_1[0] == candidates_3[0]) &&
                                (candidates_1[1] == candidates_2[1] && candidates_1[1] == candidates_3[1]) &&
                                (candidates_1[2] == candidates_2[2] && candidates_1[2] == candidates_3[2])) {
                                
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

                                        if (is_candidate(p_cells[l], candidates_1[0]) || is_candidate(p_cells[l], candidates_1[1]) || is_candidate(p_cells[l], candidates_1[2])) 
                                        {
                                            p_unset_array[*p_unset].p_cell = p_cells[l];
                                            p_unset_array[*p_unset].candidate_1 = candidates_1[0];
                                            p_unset_array[*p_unset].candidate_2 = candidates_1[1];
                                            p_unset_array[*p_unset].candidate_3 = candidates_1[2];
                                            (*p_unset)++;
                                        }
                                    }
                                }
                            }
                            free(candidates_1);
                            free(candidates_2);
                            free(candidates_3);
                        }
                    }
                }
            }
        }
    }
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