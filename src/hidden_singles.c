#include "hidden_singles.h"
#include "sudoku.h"

int find_hidden_single_values(Cell **p_cells, int *hidden_single_values)
{
    int count = 0;

    for (int value = 1; value <= BOARD_SIZE; ++value)
    {
        bool isHiddenSingle = true;

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            if (p_cells[i]->num_candidates > 1 && is_candidate(p_cells[i], value))
            {
                isHiddenSingle = false;
                break;
            }
        }

        if (isHiddenSingle)
        {
            hidden_single_values[count++] = value;
        }
    }

    return count;
}

void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter)
{
    int hidden_single_values[BOARD_SIZE];
    int count = find_hidden_single_values(p_cells, hidden_single_values);

    for (int i = 0; i < count && *p_counter < BOARD_SIZE * 3; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (is_candidate(p_cells[j], hidden_single_values[i]))
            {
                p_hidden_singles[*p_counter].p_cell = p_cells[j];
                p_hidden_singles[*p_counter].value = hidden_single_values[i];
                (*p_counter)++;
                break;
            }
        }
    }
}

int hidden_singles(SudokuBoard *p_board)
{
    int counter = 0;
    HiddenSingle hidden_singles[BOARD_SIZE * 3];

    // Check hidden singles in rows
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &counter);
    }

    // Check hidden singles in columns
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        find_hidden_single(p_board->p_cols[i], hidden_singles, &counter);
    }

    // Check hidden singles in boxes
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        find_hidden_single(p_board->p_boxes[i], hidden_singles, &counter);
    }

    // Apply the hidden singles
    for (int i = 0; i < counter; ++i)
    {
        Cell *cell = hidden_singles[i].p_cell;
        int value = hidden_singles[i].value;
        set_candidates(cell, &value, 1);
    }

    return counter;
}