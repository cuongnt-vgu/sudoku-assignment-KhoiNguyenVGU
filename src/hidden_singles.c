#include "hidden_singles.h"

bool is_in_list_hidden_single(HiddenSingle *p_array, Cell *p, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        if (p == p_array[i].p_cell) 
        {
            return true;
        }
    }
    return false;
}

int find_hidden_single_value(Cell **cells, int *hidden_single_value) 
{
    int count = 0;
    int num_candidates[BOARD_SIZE] = {0};

    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        if (cells[i]->num_candidates > 1) 
        {
            int *candidates = get_candidates(cells[i]);

            for (int j = 0; j < cells[i]->num_candidates; j++) 
            {
                num_candidates[candidates[j] - 1]++;
            }

            free(candidates);
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        if (num_candidates[i] == 1) 
        {
            hidden_single_value[count++] = i + 1;
        }
    }

    return count;
}

void find_hidden_single(Cell **cells, HiddenSingle *hidden_single, int *p_counter) 
{
    int hidden_single_values[BOARD_SIZE];
    int num_values = find_hidden_single_value(cells, hidden_single_values);

    for (int i = 0; i < num_values; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            if (cells[j]->num_candidates > 1) 
            {
                int *candidates = get_candidates(cells[j]);

                for (int k = 0; k < cells[j]->num_candidates; k++) 
                {
                    if (candidates[k] == hidden_single_values[i] && !is_in_list_hidden_single(hidden_single, cells[j], *p_counter)) 
                    {
                        hidden_single[*p_counter] = (HiddenSingle){cells[j], hidden_single_values[i]};
                        (*p_counter)++;
                    }
                }
                
                free(candidates);
            }
        }
    }
}

int hidden_singles(SudokuBoard *p_board) 
{
    int hidden_singles_counter = 0;
    HiddenSingle hidden_singles[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &hidden_singles_counter);
        find_hidden_single(p_board->p_cols[i], hidden_singles, &hidden_singles_counter);
        find_hidden_single(p_board->p_boxes[i], hidden_singles, &hidden_singles_counter);
    }

    for (int i = 0; i < hidden_singles_counter; i++) 
    {
        int single_value = hidden_singles[i].value;
        set_candidates(hidden_singles[i].p_cell, &single_value, 1);
    }

    return hidden_singles_counter;
}