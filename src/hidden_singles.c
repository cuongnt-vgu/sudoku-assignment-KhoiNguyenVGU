#include "hidden_singles.h"

#include <stdlib.h>

int find_hidden_single_values(Cell **p_cells, int *hidden_single_values)
{
    int num_out = 0;

    int candidate_counter[BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        candidate_counter[i] = 0;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->num_candidates > 1)
        {
            int *candidates = get_candidates(p_cells[i]);
            for (int j = 0; j < p_cells[i]->num_candidates; j++)
            {
                candidate_counter[candidates[j] - 1]++;
            }
            free(candidates);
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (candidate_counter[i] == 1)
        {
            hidden_single_values[num_out++] = i + 1;
        }
    }
    return num_out;
}

bool is_in_list_hidden_singles(HiddenSingle *p_array, int size, Cell *p)
{
    for (int i = 0; i < size; i++)
    {
        if (p_array[i].p_cell == p)
        {
            return true;
        }
    }
    return false;
}

void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles,
                        int *p_counter)
{
    int hidden_single_values[BOARD_SIZE];
    int num_values = find_hidden_single_values(p_cells, hidden_single_values);

    for (int i = 0; i < num_values; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_cells[j]->num_candidates > 1)
            {
                int *candidates = get_candidates(p_cells[j]);
                for (int k = 0; k < p_cells[j]->num_candidates; k++)
                {
                    if ((candidates[k] == hidden_single_values[i]) && (!is_in_list_hidden_singles(p_hidden_singles, *p_counter, p_cells[j])))
                    {
                        p_hidden_singles[(*p_counter)++] =
                            (HiddenSingle){p_cells[j], hidden_single_values[i]};
                    }
                }
                free(candidates);
            }
        }
    }
}

int hidden_singles(SudokuBoard *p_board)
{
    int hidden_single_cells_counter = 0;
    HiddenSingle hidden_single_cells[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_single(p_board->p_rows[i], hidden_single_cells,
                           &hidden_single_cells_counter);
        find_hidden_single(p_board->p_cols[i], hidden_single_cells,
                           &hidden_single_cells_counter);
        find_hidden_single(p_board->p_boxes[i], hidden_single_cells,
                           &hidden_single_cells_counter);
    }

    for (int i = 0; i < hidden_single_cells_counter; i++)
    {
        set_candidates(hidden_single_cells[i].p_cell,
                       (int *)(int[]){hidden_single_cells[i].value}, 1);
    }

    return hidden_single_cells_counter;
}
