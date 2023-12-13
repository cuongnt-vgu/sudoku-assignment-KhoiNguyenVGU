#include "hidden_triples.h"
#include "utils.h"

int hidden_triples(SudokuBoard *p_board)
{
    int triples_found = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cell *cell = &p_board->data[i][j];
            if (cell->num_candidates != 3)
                continue;

            // Check row
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                for (int l = k + 1; l < BOARD_SIZE; l++)
                {
                    for (int m = l + 1; m < BOARD_SIZE; m++)
                    {
                        if (k == j || l == j || m == j)
                            continue;
                        Cell *cell1 = &p_board->data[i][k];
                        Cell *cell2 = &p_board->data[i][l];
                        Cell *cell3 = &p_board->data[i][m];
                        if (cell1->num_candidates != 3 || cell2->num_candidates != 3 || cell3->num_candidates != 3)
                            continue;
                        for (int n = 1; n <= BOARD_SIZE; n++)
                        {
                            if (is_candidate(cell, n) && is_candidate(cell1, n) && is_candidate(cell2, n) && is_candidate(cell3, n))
                            {
                                unset_candidate(cell, n);
                                unset_candidate(cell1, n);
                                unset_candidate(cell2, n);
                                unset_candidate(cell3, n);
                                triples_found++;
                            }
                        }
                    }
                }
            }

            // Check column
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                for (int l = k + 1; l < BOARD_SIZE; l++)
                {
                    for (int m = l + 1; m < BOARD_SIZE; m++)
                    {
                        if (k == i || l == i || m == i)
                            continue;
                        Cell *cell1 = &p_board->data[k][j];
                        Cell *cell2 = &p_board->data[l][j];
                        Cell *cell3 = &p_board->data[m][j];
                        if (cell1->num_candidates != 3 || cell2->num_candidates != 3 || cell3->num_candidates != 3)
                            continue;
                        for (int n = 1; n <= BOARD_SIZE; n++)
                        {
                            if (is_candidate(cell, n) && is_candidate(cell1, n) && is_candidate(cell2, n) && is_candidate(cell3, n))
                            {
                                unset_candidate(cell, n);
                                unset_candidate(cell1, n);
                                unset_candidate(cell2, n);
                                unset_candidate(cell3, n);
                                triples_found++;
                            }
                        }
                    }
                }
            }

            // Check block
            int block_row = (i / 3) * 3;
            int block_col = (j / 3) * 3;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    for (int m = l + 1; m < 3; m++)
                    {
                        for (int n = 0; n < 3; n++)
                        {
                            for (int o = n + 1; o < 3; o++)
                            {
                                for (int p = 0; p < 3; p++)
                                {
                                    if ((block_row + k == i && block_col + l == j) || 
                                        (block_row + m == i && block_col + n == j) || 
                                        (block_row + o == i && block_col + p == j))
                                        continue;
                                    Cell *cell1 = &p_board->data[block_row + k][block_col + l];
                                    Cell *cell2 = &p_board->data[block_row + m][block_col + n];
                                    Cell *cell3 = &p_board->data[block_row + o][block_col + p];
                                    if (cell1->num_candidates != 3 || cell2->num_candidates != 3 || cell3->num_candidates != 3)
                                        continue;
                                    for (int q = 1; q <= BOARD_SIZE; q++)
                                    {
                                        if (is_candidate(cell, q) && is_candidate(cell1, q) && is_candidate(cell2, q) && is_candidate(cell3, q))
                                        {
                                            unset_candidate(cell, q);
                                            unset_candidate(cell1, q);
                                            unset_candidate(cell2, q);
                                            unset_candidate(cell3, q);
                                            triples_found++;
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

    return triples_found;
}