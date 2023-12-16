#include "naked_triples.h"
#include "utils.h"

int find_naked_triples_in_group(Cell **p_cells, NakedTriple *naked_triples, int *p_counter)
{
    int counter = 0;

    for (int i = 0; i < BOARD_SIZE - 2; i++)
    {
        for (int j = i + 1; j < BOARD_SIZE - 1; j++)
        {
            for (int k = j + 1; k < BOARD_SIZE; k++)
            {
                if (same_candidates(p_cells[i], p_cells[j]) && same_candidates(p_cells[i], p_cells[k]) && p_cells[i]->num_candidates == 3)
                {
                    naked_triples[counter++] = (NakedTriple){{p_cells[i], p_cells[j], p_cells[k]}, {p_cells[i]->candidates[0], p_cells[i]->candidates[1], p_cells[i]->candidates[2]}};
                }
            }
        }
    }

    *p_counter = counter;
    return counter;
}

void remove_naked_triple_candidates(Cell **p_cells, NakedTriple naked_triple)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i] != naked_triple.p_cells[0] && p_cells[i] != naked_triple.p_cells[1] && p_cells[i] != naked_triple.p_cells[2] && p_cells[i]->num_candidates > 1)
        {
            unset_candidate(p_cells[i], naked_triple.values[0]);
            unset_candidate(p_cells[i], naked_triple.values[1]);
            unset_candidate(p_cells[i], naked_triple.values[2]);
        }
    }
}

int naked_triples(SudokuBoard *p_board)
{
    int naked_triple_counter = 0;
    NakedTriple naked_triples[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // Check in rows
        naked_triple_counter += find_naked_triples_in_group(p_board->p_rows[i], naked_triples + naked_triple_counter, &naked_triple_counter);

        // Check in columns
        naked_triple_counter += find_naked_triples_in_group(p_board->p_cols[i], naked_triples + naked_triple_counter, &naked_triple_counter);

        // Check in boxes
        naked_triple_counter += find_naked_triples_in_group(p_board->p_boxes[i], naked_triples + naked_triple_counter, &naked_triple_counter);
    }

    for (int i = 0; i < naked_triple_counter; i++)
    {
        remove_naked_triple_candidates(naked_triples[i].p_cells, naked_triples[i]);
    }

    return naked_triple_counter;
}