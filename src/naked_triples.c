#include "naked_triples.h"
#include "utils.h"

int naked_triples(SudokuBoard *p_board)
{
    int triples_found = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cell *cell = &p_board->data[i][j];
            if (cell->num_candidates < 2 || cell->num_candidates > 3)
                continue;

            // Check row, column, and block
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                // Check row
                if (k != j && check_triple(p_board, i, j, i, k))
                    triples_found++;

                // Check column
                if (k != i && check_triple(p_board, i, j, k, j))
                    triples_found++;
            }

            // Check block
            int start_row = (i / 3) * 3;
            int start_col = (j / 3) * 3;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if ((start_row + k != i || start_col + l != j) && check_triple(p_board, i, j, start_row + k, start_col + l))
                        triples_found++;
                }
            }
        }
    }

    return triples_found;
}

int check_triple(SudokuBoard *p_board, int row1, int col1, int row2, int col2)
{
    Cell *cell1 = &p_board->data[row1][col1];
    Cell *cell2 = &p_board->data[row2][col2];

    if (cell2->num_candidates < 2 || cell2->num_candidates > 3)
        return 0;

    int combined_candidates[3] = {0};
    int num_combined = 0;
    for (int i = 0; i < cell1->num_candidates; i++)
    {
        combined_candidates[num_combined++] = cell1->candidates[i];
    }
    for (int i = 0; i < cell2->num_candidates; i++)
    {
        if (!contains(combined_candidates, num_combined, cell2->candidates[i]))
        {
            if (num_combined == 3)
                return 0;
            combined_candidates[num_combined++] = cell2->candidates[i];
        }
    }

    if (num_combined != 3)
        return 0;

    // If we get here, cell1 and cell2 form a naked triple with combined_candidates.
    // We can remove these candidates from all other cells in the same row, column, and block.
    remove_other_candidates(p_board, row1, col1, row2, col2, combined_candidates, num_combined);

    return 1;
}

void remove_other_candidates(SudokuBoard *p_board, int row1, int col1, int row2, int col2, int *candidates, int num_candidates)
{
    // Remove candidates from other cells in the same row
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (j != col1 && j != col2)
        {
            for (int k = 0; k < num_candidates; k++)
            {
                unset_candidate(&p_board->data[row1][j], candidates[k]);
            }
        }
    }

    // Remove candidates from other cells in the same column
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (i != row1 && i != row2)
        {
            for (int k = 0; k < num_candidates; k++)
            {
                unset_candidate(&p_board->data[i][col1], candidates[k]);
            }
        }
    }

    // Remove candidates from other cells in the same block
    int start_row = (row1 / 3) * 3;
    int start_col = (col1 / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ((start_row + i != row1 || start_col + j != col1) && (start_row + i != row2 || start_col + j != col2))
            {
                for (int k = 0; k < num_candidates; k++)
                {
                    unset_candidate(&p_board->data[start_row + i][start_col + j], candidates[k]);
                }
            }
        }
    }
}