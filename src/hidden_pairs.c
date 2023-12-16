#include "hidden_pairs.h"
#include "utils.h"
#include <stdlib.h>

int find_hidden_pairs(Cell **p_cells, HiddenPair *hidden_pairs) {
    int num_pairs = 0;

    for (int val1 = 1; val1 <= BOARD_SIZE; val1++) {
        for (int val2 = val1 + 1; val2 <= BOARD_SIZE; val2++) {
            Cell *cells_with_pair[2];
            int count = 0;

            for (int i = 0; i < BOARD_SIZE; i++) {
                if (is_candidate(p_cells[i], val1) && is_candidate(p_cells[i], val2)) {
                    if (count < 2) {
                        cells_with_pair[count] = p_cells[i];
                    }
                    count++;
                }
            }

            if (count == 2 && (cells_with_pair[0]->num_candidates > 2 || cells_with_pair[1]->num_candidates > 2)) {
                hidden_pairs[num_pairs++] = (HiddenPair){{cells_with_pair[0], cells_with_pair[1]}, {val1, val2}};
            }
        }
    }

    return num_pairs;
}

bool is_in_list_hidden_pairs(HiddenPair *p_array, int size, Cell **p_cells, int *values) {
    for (int i = 0; i < size; i++) {
        if ((p_cells[0] == p_array[i].p_cells[0] && p_cells[1] == p_array[i].p_cells[1]) ||
            (p_cells[0] == p_array[i].p_cells[1] && p_cells[1] == p_array[i].p_cells[0]) ||
            (values[0] == p_array[i].values[0] && values[1] == p_array[i].values[1]) ||
            (values[0] == p_array[i].values[1] && values[1] == p_array[i].values[0])) {
            return true;
        }
    }
    return false;
}

void find_hidden_pairs_in_group(Cell **p_group, HiddenPair *hidden_pairs, int *p_counter) {
    int pairs_in_group = find_hidden_pairs(p_group, hidden_pairs);
    for (int i = 0; i < pairs_in_group; i++) {
        unset_other_candidates(hidden_pairs[i].p_cells[0], hidden_pairs[i].values, 2);
        unset_other_candidates(hidden_pairs[i].p_cells[1], hidden_pairs[i].values, 2);
        (*p_counter)++;
    }
}

int hidden_pairs(SudokuBoard *p_board) {
    int hidden_pairs_counter = 0;
    HiddenPair hidden_pairs[BOARD_SIZE * BOARD_SIZE];

    // Check rows for hidden pairs
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_pairs_in_group(p_board->p_rows[i], hidden_pairs, &hidden_pairs_counter);
    }

    // Check columns for hidden pairs
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_pairs_in_group(p_board->p_cols[i], hidden_pairs, &hidden_pairs_counter);
    }

    // Check boxes for hidden pairs
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_pairs_in_group(p_board->p_boxes[i], hidden_pairs, &hidden_pairs_counter);
    }

    return hidden_pairs_counter;
}