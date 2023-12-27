#include "naked_triples.h"

bool is_in_triples(int triple_value[3], int value)
{
    for (int i = 0; i < 3; i++)
    {
        if (triple_value[i] == value)
        {
            return true;
        }
    }

    return false;
}

bool is_cell_in_triples(Cell* p_cell, int triple_value[3])
{
    int* candidates_value = get_candidates(p_cell);

    for (int i = 0; i < p_cell->num_candidates; i++)
    {
        if (!is_in_triples(triple_value, candidates_value[i]))
        {
            free(candidates_value);
            return false;
        }
    }

    free(candidates_value);

    return true;
}

int check_naked_triples(Cell **p_cells, int *triples, int *index)
{
    int counter = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->num_candidates == 1 || p_cells[i]->num_candidates > 3) 
        {
            continue;
        }

        else if (is_cell_in_triples(p_cells[i], triples)) 
        {
            index[counter++] = i;
        }
    }

    return counter == 3;
}

void find_naked_triples(Cell **p_cells, NakedTriples *triples, int *counter, int is_box)
{
    int candidates_counter[BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        candidates_counter[i] = 0;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        int* candidates_value = get_candidates(p_cells[i]);

        for (int j = 0; j < p_cells[i]->num_candidates; j++)
        {
            candidates_counter[candidates_value[j]-1] += 1;
        }

        free(candidates_value);
    }

    int naked_triples[BOARD_SIZE];
    int naked_triples_counter = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (candidates_counter[i] > 1)
        {
            naked_triples[naked_triples_counter++] = i + 1;
        }
    }

    if (naked_triples_counter < 3) 
    {
        return;
    }

    for (int i = 0; i < naked_triples_counter - 2; i++)
    {
        for (int j = i + 1; j < naked_triples_counter - 1; j++)
        {
            for (int k = j + 1; k < naked_triples_counter; k++)
            {
                int value[3] = {naked_triples[i], naked_triples[j], naked_triples[k]};
                int index[BOARD_SIZE];
                
                if (check_naked_triples(p_cells, value, index))
                {
                    if (is_box == 1)
                    {
                        if (p_cells[index[0]]->row_index == p_cells[index[1]]->row_index && p_cells[index[1]]->row_index == p_cells[index[2]]->row_index) 
                        {
                            continue;
                        }

                        if (p_cells[index[0]]->col_index == p_cells[index[1]]->col_index && p_cells[index[1]]->col_index == p_cells[index[2]]->col_index) 
                        {
                            continue;
                        }
                    }

                    triples[(*counter)++] = (NakedTriples){p_cells, {index[0], index[1], index[2]}, {naked_triples[i], naked_triples[j], naked_triples[k]}};
                }
            }
        }
    }
}

int naked_triples(SudokuBoard *board)
{
    int triple_count = 0;
    NakedTriples naked_triple[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_triples(board->p_rows[i], naked_triple, &triple_count, 0);
        find_naked_triples(board->p_cols[i], naked_triple, &triple_count, 0);
        find_naked_triples(board->p_boxes[i], naked_triple, &triple_count, 1);
    }

    for (int i = 0; i < triple_count; i++)
    {
        Cell** cells = naked_triple[i].p_cells;

        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (j != naked_triple[i].index[0] && j != naked_triple[i].index[1] && j != naked_triple[i].index[2])
            {
                for (int k = 0; k < 3; k++)
                {
                    if (is_candidate(cells[j], naked_triple[i].value[k]))
                    {
                        unset_candidate(cells[j], naked_triple[i].value[k]);
                    }
                }
            }
        }
    }
    
    return triple_count;
}